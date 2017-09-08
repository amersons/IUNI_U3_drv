/*******************************************************************************
 *
 * Description: 
 *		Define ScaladoPanorama to deal with panorama.
 *
 * Author  : wutangzhi
 * Email   : wutz@gionee.com
 * Date    : 2012-08-11
 *
 *******************************************************************************/

#include <stdlib.h>

#include "ScaladoPanorama.h"

namespace android {

static PanoramaLens LENS_16_TO_9 = {
	{2048.0, 2048.0},
	{1024.0, 576.0}, 
	0.0, 
	{0.0, 0.0, 0.0, 0.0, 0.0}, 
	2048, 
	1152
	};

static PanoramaLens LENS_4_TO_3 = {
	{640.0, 640.0},
	{320.0, 240.0}, 
	0.0, 
	{0.0, 0.0, 0.0, 0.0, 0.0},
	640, 
	480
	};

ScaladoPanorama::
ScaladoPanorama() :
	mTracker(NULL),
	mTransform(NULL),
	mEngine(NULL),
	mImageNum(0),
	mImageIndex(0),
	mDirection(PANORAMA_DIRECTION_UNKNOWN),
	mEnabledTrack(true),
	mLastImage(NULL),
	mFilePath(NULL),
	mListener(NULL),
	mExifSession(NULL),
	mLastDxDy({0})
{
	::memset(mImageArray, 0, sizeof(mImageArray));
	pthread_mutex_init(&mMutex, NULL);   
}

ScaladoPanorama::
~ScaladoPanorama() 
{
	pthread_mutex_destroy(&mMutex);  
}

void 
ScaladoPanorama::
deinit() 
{
	release();
}

void
ScaladoPanorama::
release() 
{
	if (mTracker != NULL) {
		caps_vftrackerDestroy(mTracker);
		mTracker = NULL;
	}

	if (mTransform != NULL) {
		caps_panoramaTransformDestroy(mTransform);
		mTransform = NULL;
	}

	if (mEngine != NULL) {
		caps_panoramaDestroy(mEngine);
		mEngine = NULL;
	}
		
	if (mExifSession != NULL) {
		exif_destroySession(mExifSession);
		mExifSession = NULL;
	}

	if (mLastImage != NULL) {
		caps_destroyImage(mLastImage);
		mLastImage = NULL;
	}

	for (int i = 0; i < 10; i ++) {
		caps_destroyImage(mImageArray[i]);
		mImageArray[i] = NULL;
	}
	
	mImageNum = 0;
	mImageIndex = 0;
	mEnabledTrack = true;
	mLastDxDy = {0};
	mLastImage = NULL;
	mListener = NULL;
	mFilePath = NULL;
	mDirection = PANORAMA_DIRECTION_UNKNOWN;
}


CRESULT 
ScaladoPanorama::
setListener(GNCameraFeatureListener* listener) 
{
	CRESULT res = CERR_OK;

	mListener = listener;
	
	return res;
}

CRESULT
ScaladoPanorama::
setCapturePath(const char* filePath)
{
	CRESULT res = CERR_OK;

	mFilePath = filePath;

	return res;
}

CRESULT 
ScaladoPanorama::
track(CTSession session) 
{
	CRESULT res = CERR_OK;
	CTImage* image = NULL;
	CTSize size= {0, 0};
	CTVector pDxDy= {0};
	CTuint32 scanline = 0;
	CTbool flag = false;
	int32 ext1 = 0;
	int32 ext2 = 0;
	int32 x = 0;
	int32 y = 0;
	int32 xOffset = 0;
	int32 yOffset = 0;
	PanoramaDirection direction = PANORAMA_DIRECTION_UNKNOWN;
	int directionTrigger = 0;

	pthread_mutex_lock(&mMutex);
	
	if (mImageNum <= mImageIndex || !mEnabledTrack) {
		pthread_mutex_unlock(&mMutex);
		return res;
	}

	res = caps_getSourceImageSize(session, &size);
	if(res != CERR_OK) {
		PRINTE_RES("caps_getSourceImageSize fail", res);
		goto EXIT;
	}

	if (mTracker == NULL) {
		res = caps_vftrackerCreateEx(&mTracker, size, CTVFTRACKERTYPE_MULTIREGION);
		if (res != CERR_OK) {
			PRINTE_RES("caps_vftrackerCreate fail", res);
			goto EXIT;
		}
	}

	if (mTransform == NULL) {
		res = caps_panoramaTransformCreate(&mTransform);
		if (res != CERR_OK) {
			PRINTE_RES("caps_panoramaTransformCreate fail", res);
			goto EXIT;
		}
	}

	scanline = caps_pixelBitSize(CM_YUV420P) * size.w / 8;
	if(res != CERR_OK) {
		PRINTE_RES("Failed to create image", res);
		goto EXIT;
	}

	if((res = caps_createImage(0, size, scanline, CM_YUV420P, &image)) != CERR_OK) {
	   PRINTE_RES("create input image fail", res);
	   goto EXIT;
	}

	res = caps_renderAsRawToBuffer(session, image, CAPS_OUTPUT_PRESERVE_AR, 0);
	if(res != CERR_OK) {
		PRINTE_RES("caps_renderAsRawToBuffer fail", res);
		goto EXIT;
	}

	res = caps_vftrackerRegisterImage(mTracker, image, mTransform);
	if (res != CERR_OK) {
		PRINTE_RES("caps_vftrackerRegisterImage fail", res);
		goto EXIT;
	}

	caps_panoramaTransformGetTranslation(mTransform, &pDxDy, &size);

	if (mDirection == PANORAMA_DIRECTION_UNKNOWN) {
		directionTrigger = PANORAMA_DIRECTION_TRIGGER + 10;
	} else {
		directionTrigger = PANORAMA_DIRECTION_TRIGGER;
	}

	if (caps_panoramaTransformGetDirection(mTransform, &direction, directionTrigger)) {		
		if (mDirection == PANORAMA_DIRECTION_UNKNOWN) {
			mDirection = direction;
		} else {
			if (mListener != NULL) {
				getTranslationForWindow(direction, pDxDy, size, &x, &y);
	
				//ext1 = ((0x0000FFFF & direction) << 16) + (0x0000FFFF & GN_PANORAMA_MSG_TYPE_XY);
				ext1 = ((0x0000FFFF & mDirection) << 16) + (0x0000FFFF & GN_PANORAMA_MSG_TYPE_XY);
				ext2 = ((0x0000FFFF & x) << 16) + (0x0000FFFF & y);
				mListener->notify(GN_CAMERA_MSG_TYPE_PANORAMA, ext1, ext2);
			}
		} 
	}
	
	if (mImageIndex != 0) {
		if (caps_panoramaTransformIsTimeToCapture(mTransform, mDirection, PANORAMA_OVERLAP)) {
			if (isLockedHorizontal(mDirection)) {
				x = (mDirection == PANORAMA_DIRECTION_RIGHT) ? pDxDy.x : -pDxDy.x;
				y = pDxDy.y;
				xOffset = abs(x - size.w * (100 - PANORAMA_OVERLAP) / 100);
				yOffset = abs(mLastDxDy.y - y);
			} else if (isLockedVertical(mDirection)) {
				x = pDxDy.x;
				y = (mDirection == PANORAMA_DIRECTION_UP) ? -pDxDy.y : pDxDy.y;
				xOffset = abs(mLastDxDy.x - pDxDy.x);
				yOffset = abs(y - size.h * (100 - PANORAMA_OVERLAP) / 100);
			}

			if (xOffset > PANORAMA_OFFSET_MAX || yOffset > PANORAMA_OFFSET_MAX) {
				goto EXIT;
			}

			mLastDxDy.x = pDxDy.x;
			mLastDxDy.y = pDxDy.y;
			
			if (mListener != NULL) {
				flag = true;
				mEnabledTrack = false;
				
				if (mLastImage != NULL) {
					caps_destroyImage(mLastImage);
				}
				
				mLastImage = image;
				
				mListener->notify(GN_CAMERA_MSG_TYPE_PANORAMA, GN_PANORAMA_MSG_TYPE_CAPTURE, 0x01);
			}
		}
	}else {
		if (mListener != NULL) {	
			flag = true;
			mEnabledTrack = false;
	
			if (mLastImage != NULL) {
				caps_destroyImage(mLastImage);
			}
			
			mLastImage = image;
			
			mListener->notify(GN_CAMERA_MSG_TYPE_PANORAMA, GN_PANORAMA_MSG_TYPE_CAPTURE, 0x01);
		}
	}

EXIT:
	if (!flag) {
		if (image != NULL) {
			caps_destroyImage(image);
			image = NULL;
		}
	}

	pthread_mutex_unlock(&mMutex);

	return res;
}

CRESULT 
ScaladoPanorama::
addImage(CTImage* image, CTSize size) 
{
	CRESULT res = CERR_OK;
	CTVector pDxDy_1 = {0, 0};
	CTVector pDxDy_2 = {0, 0};
	CTSize pSize = {0, 0};

	if (mImageIndex >= mImageNum) {
		PRINTE("The mImageIndex is greater or equal than the mImageNum.");
		return res;
	}

	mImageArray[mImageIndex++] = image;

	if (mImageIndex == 1) {
		goto EXIT;
	}
	
	if (mEngine == NULL) {
		res = caps_panoramaCreate(&mEngine, &LENS_4_TO_3, size, mDirection);
		if (res != CERR_OK) {
			PRINTE_RES("caps_panoramaCreate fail", res);
			goto EXIT;
		}

		if (isLockedHorizontal(mDirection)) {
			res = caps_panoramaSetBlendMode(mEngine, 
				PANORAMA_BLEND_MODE_MULTILEVEL_BEST | PANORAMA_BLEND_MODE_OPT_NO_COLOR_COMP);
			if (res != CERR_OK) {
				PRINTE_RES("caps_panoramaSetBlendMode failed.", res);
				goto EXIT;
			}
		}
	}

	if (mImageIndex == 2) {
		caps_panoramaTransformGetTranslation(mTransform, &pDxDy_2, &pSize);
		res = caps_panoramaTransformSetTranslation(mTransform, &pDxDy_1, &pSize);
		if (res != CERR_OK) {
			PRINTE_RES("caps_panoramaTransformSetTranslation fail", res);
			goto EXIT;
		}

		res = caps_panoramaAddImageRaw(mEngine, mImageArray[0], mTransform);
		if (res != CERR_OK) {
			PRINTE_RES("caps_panoramaAddImageRaw fail", res);
			goto EXIT;
		}

		res = caps_panoramaTransformSetTranslation(mTransform, &pDxDy_2, &pSize);
		if (res != CERR_OK) {
			PRINTE_RES("caps_panoramaTransformSetTranslation fail", res);
			goto EXIT;
		}
	}
	
	res = caps_panoramaAddImageRaw(mEngine, mImageArray[mImageIndex - 1], mTransform);
	if (res != CERR_OK) {
		PRINTE_RES("caps_panoramaAddImageRaw fail", res);
	}

EXIT:
	mEnabledTrack = true;
	caps_vftrackerStartOver(mTracker);

	if (mImageIndex < mImageNum) {
		res = caps_vftrackerRegisterImage(mTracker, mLastImage, mTransform);
		if (res != CERR_OK) {
			PRINTE_RES("caps_vftrackerRegisterImage failed", res);;
		}
	}

	return res;
}


CRESULT 
ScaladoPanorama::
addImage(CTSession session, CTExifSession exifSession) 
{
	CRESULT res = CERR_OK;
	CTImage* image = NULL;
	CTSize size= {0, 0};
	CTuint32 scanline = 0;
	CTSession sess;

	pthread_mutex_lock(&mMutex);
	
	if (mImageIndex >= mImageNum) {
		PRINTE("The mImageIndex is greater or equal than the mImageNum.");
		pthread_mutex_unlock(&mMutex);
		return res;
	}

	if (mImageIndex == 0) {
		res = exif_copySession(&mExifSession, exifSession);
		if (res != CERR_OK) {
			mExifSession = NULL;
			PRINTE_RES("exif_copySession failed", res);
		}
	}

	res = caps_getSourceImageSize(session, &size);
	if(res != CERR_OK) {
		PRINTE_RES("caps_getSourceImageSize fail", res);
		goto EXIT;
	}

	scanline = caps_pixelBitSize(CM_YUV420P) * size.w / 8;
	if(res != CERR_OK) {
		PRINTE_RES("Failed to create image", res);
		goto EXIT;
	}

	if((res = caps_createImage(0, size, scanline, CM_YUV420P, &image)) != CERR_OK) {
	   PRINTE_RES("create input image fail", res);
	   goto EXIT;
	}

	res = caps_renderAsRawToBuffer(session, image, CAPS_OUTPUT_PRESERVE_AR, 0);
	if(res != CERR_OK) {
		PRINTE_RES("caps_renderAsRawToBuffer fail", res);
		goto EXIT;
	}

	res = addImage(image, size);
	if (res != CERR_OK) {
		PRINTE_RES("addImage failed", res);
	}

EXIT:
	mEnabledTrack = true;

	pthread_mutex_unlock(&mMutex);

	return res;
}

CRESULT 
ScaladoPanorama::
startAUTORAMA(int32 num)
{
	CRESULT res = CERR_OK;

	pthread_mutex_lock(&mMutex);
	
	if (num <= PANORAMA_NUM_MAX) {
		if (mTracker != NULL) {
			caps_vftrackerStartOver(mTracker);
		}

		mImageNum = num;
	} else {
		res = CERR_INVALID_PARAMETER;
		PRINTE("The num is greater than PANORAMA_NUM_MAX.");
	}
	
	pthread_mutex_unlock(&mMutex);

	return res;
}

CRESULT 
ScaladoPanorama::
stopAUTORAMA(int32 isMerge)
{
	CRESULT res = CERR_OK;

	pthread_mutex_lock(&mMutex);
	
	if (isMerge) {
		res = mosaicImage();
		if (res != CERR_OK) {
			PRINTE_RES("mosaicImage failed.", res);
		}
	} else {
		release();
	}
	
	pthread_mutex_unlock(&mMutex);

	return res;
}

CTbool
ScaladoPanorama::
isLockedVertical(PanoramaDirection direction)
{
	CTbool res = false;

	if ((mDirection == PANORAMA_DIRECTION_UP || mDirection == PANORAMA_DIRECTION_DOWN)
		&& (direction == PANORAMA_DIRECTION_UP || direction == PANORAMA_DIRECTION_DOWN )) {
		res = true;
	}
	
	return res;
}

CTbool
ScaladoPanorama::
isLockedHorizontal(PanoramaDirection direction)
{
	CTbool res = false;

	if ((mDirection == PANORAMA_DIRECTION_RIGHT|| mDirection == PANORAMA_DIRECTION_LEFT)
		&& (direction == PANORAMA_DIRECTION_RIGHT|| direction == PANORAMA_DIRECTION_LEFT)) {
		res = true;
	}
	
	return res;
}

CTbool
ScaladoPanorama::
isLockedDirection(PanoramaDirection direction)
{
	CTbool res = false;

	return res;
}

CRESULT
ScaladoPanorama::
mosaicImage()
{
	CRESULT res = CERR_OK;
	CTSession sess = NULL;
	CTSize size = {0};

	if (mImageIndex > 1) {
		res = caps_newSessionWithExternalPanorama(mEngine, &sess);
		if (res != CERR_OK) {
			PRINTE_RES("caps_newSessionWithExternalPanorama fail", res);
			goto EXIT;
		}
	} else {
		res = caps_newSessionWithRaw(mImageArray[0], &sess);
		if (res != CERR_OK) {
			PRINTE_RES("caps_newSessionWithExternalPanorama fail", res);
			goto EXIT;
		}
	}

	if (mExifSession != NULL) {
		res = exif_addExifHeaderFromSession(sess, mExifSession);
		if (res != CERR_OK) {
			PRINTE_RES("exif_addExifHeaderFromSession fail", res);
		}
	}

	res = caps_getSourceImageSize(sess, &size);
	if (res != CERR_OK) {
		PRINTE_RES("caps_getSourceImageSize fail", res);
		goto EXIT;
	}
	
	res = caps_renderToFile(sess, mFilePath, size, CAPS_OUTPUT_PRESERVE_AR, IMAGE_FORMAT_JPEG, 0);
	if (res != CERR_OK) {
		PRINTE_RES("Failed to render to file", res);
	}

EXIT:
	if (mListener != NULL) {
		mListener->notify(GN_CAMERA_MSG_TYPE_PANORAMA, GN_PANORAMA_MSG_TYPE_CAPTURE, 0);
	}

	if (sess != NULL) {
		caps_destroySession(sess);
		sess = NULL;
	}
	
	release();
	
	return res;
}

void
ScaladoPanorama::
getTranslationForWindow(
	PanoramaDirection direction, CTVector pDxDy, CTSize size, int32* x, int32* y)
{
	switch (direction) {
		case PANORAMA_DIRECTION_RIGHT:
		case PANORAMA_DIRECTION_LEFT:
			*x = pDxDy.x * TARGET_DISTANCE_HORIZONTAL / (size.w * (100 - PANORAMA_OVERLAP) / 100);
			*y = pDxDy.y;
			break;
		case PANORAMA_DIRECTION_UP:
		case PANORAMA_DIRECTION_DOWN:
			*x = pDxDy.x;
			*y = pDxDy.y * TARGET_DISTANCE_VERTICAL / (size.h * (100 - PANORAMA_OVERLAP) / 100);
			break;
		default:
			PRINTE("unknown direction.");
			break;
	}
}

};



