/*************************************************************************************
 * 
 * Description:
 * 	Defines ArcSoft APIs for camera HAL.
 *
 * Author : wutangzhi
 * Email  : wutz@gionee.com
 * Date   : 2013-03-15
 *
 *************************************************************************************/
#define LOG_TAG "ArcSoftCameraFeature"
#include <android/log.h>
#include <cutils/properties.h>
#include <stdlib.h>

#include "ArcSoftCameraFeature.h"
 
namespace android {

static int count_dump = 0;

ArcSoftCameraFeature::ArcSoftCameraFeature() 
	: mGNCameraFeature(GN_CAMERA_FEATURE_NONE)
	, mListener(NULL)
	, mOrientation(0)
	, mFormat(GN_IMG_FORMAT_NONE)
	, mArcSoftNightShot(NULL)
	, mArcSoftSceneDetection(NULL)
	, mArcSoftFaceBeauty(NULL)
	, mArcSoftGestureShot(NULL)
	, mArcSoftLiveEffect(NULL)
	, mArcSoftPicZoom(NULL)
	, mPreviewBufferSize(0)
	, mWidth(0)
	, mHeight(0)
{
	char value[PROPERTY_VALUE_MAX] = {0};
	property_get("arcsoft.dumpbuffer", value, "0");
	mDumpImage = (atoi(value) != 0);
	
	//Create ArcSoftFaceBeauty object
	mArcSoftFaceBeauty = new ArcSoftFaceBeauty();
	if (mArcSoftFaceBeauty == NULL) {
		PRINTE("Failed to new ArcSoftFaceBeauty");
	}

	//Create ArcSoftGestureShot object
	mArcSoftGestureShot = new ArcSoftGestureShot();
	if (mArcSoftGestureShot == NULL) {
		PRINTE("Failed to new ArcSoftGestureShot");
	}

	//Create ArcSoftNightShot object
	mArcSoftNightShot = new ArcSoftNightShot();
	if (mArcSoftNightShot == NULL) {
		PRINTE("Failed to new ArcSoftNightShot");
	}

	//Create ArcSoftSceneDetection object
	mArcSoftSceneDetection = new ArcSoftSceneDetection();
	if (mArcSoftSceneDetection == NULL) {
		PRINTE("Failed to new ArcSoftSceneDetection");
	}

	//Create ArcSoftLiveEffect object
	mArcSoftLiveEffect = new ArcSoftLiveEffect();
	if (mArcSoftLiveEffect == NULL) {
		PRINTE("Failed to new ArcSoftLiveEffect");
	}

	//Create ArcSoftAgeGenderDetection object
	mArcSoftAgeGenderDetection = new ArcSoftAgeGenderDetection();
	if (mArcSoftAgeGenderDetection == NULL) {
		PRINTE("Failed to new ArcSoftAgeGenderDetection");
	}

	mArcSoftPicZoom = new ArcSoftPicZoom();
	if (mArcSoftPicZoom == NULL) {
		PRINTE("Failed to new mArcSoftPicZoom");
	}

	pthread_mutex_init(&mMutex, NULL);
}

ArcSoftCameraFeature::
~ArcSoftCameraFeature() 
{
	if (mArcSoftFaceBeauty != NULL) {
		delete mArcSoftFaceBeauty;
		mArcSoftFaceBeauty = NULL;
	}

	if (mArcSoftGestureShot != NULL) {
		delete mArcSoftGestureShot;
		mArcSoftGestureShot = NULL;
	}

	if (mArcSoftNightShot != NULL) {
		delete mArcSoftNightShot;
		mArcSoftNightShot = NULL;
	}

	if (mArcSoftSceneDetection != NULL) {
		delete mArcSoftSceneDetection;
		mArcSoftSceneDetection = NULL;
	}

	if (mArcSoftLiveEffect != NULL) {
		delete mArcSoftLiveEffect;
		mArcSoftLiveEffect = NULL;
	}

	if (mArcSoftAgeGenderDetection != NULL) {
		delete mArcSoftAgeGenderDetection;
		mArcSoftAgeGenderDetection = NULL;
	}

	if (mArcSoftPicZoom != NULL) {
		delete mArcSoftPicZoom;
		mArcSoftPicZoom = NULL;
	}

	pthread_mutex_destroy(&mMutex);  
}

ArcSoftCameraFeature*
ArcSoftCameraFeature::
createInstance() 
{
	return new ArcSoftCameraFeature();
}

void
ArcSoftCameraFeature::
destroyInstance() 
{
	delete this;
}

int32
ArcSoftCameraFeature::
init()
{
	MRESULT res = 0;

	pthread_mutex_lock(&mMutex);

	if (mArcSoftFaceBeauty != NULL) {
		res = mArcSoftFaceBeauty->init();
		if (res != 0) {
			PRINTE("Failed to initialized face beauty [%ld].", res);
		}
	}

	if (mArcSoftGestureShot != NULL) {
		res = mArcSoftGestureShot->init();
		if (res != 0) {
			PRINTE("Failed to initialized gesture shot [%ld].", res);
		}
	}

	if (mArcSoftNightShot != NULL) {
		res = mArcSoftNightShot->init();
		if (res != 0) {
			PRINTE("Failed to initialized night shot [%ld].", res);
		}
	}

	if (mArcSoftSceneDetection != NULL) {
		res = mArcSoftSceneDetection->init();
		if (res != 0) {
			PRINTE("Failed to initialized scene detection [%ld].", res);
		}
	}

	if (mArcSoftLiveEffect != NULL) {
		res = mArcSoftLiveEffect->init();
		if (res != 0) {
			PRINTE("Failed to initialized live effect [%ld].", res);
		}
	}

	if (mArcSoftAgeGenderDetection != NULL) {
		res = mArcSoftAgeGenderDetection->init();
		if (res != 0) {
			PRINTE("Failed to initialized age gender detection [%ld].", res);
		}
	}

	if (mArcSoftPicZoom != NULL) {
		res = mArcSoftPicZoom->init();
		if (res != 0) {
			PRINTE("Faile to initialized pic zoom [%ld].", res);
		}
	}

	pthread_mutex_unlock(&mMutex);

	return res;
}

void 
ArcSoftCameraFeature::
deinit()
{
	pthread_mutex_lock(&mMutex);

	if (mArcSoftFaceBeauty != NULL) {
		mArcSoftFaceBeauty->deinit();
	}

	if (mArcSoftGestureShot != NULL) {
		mArcSoftGestureShot->deinit();
		mArcSoftGestureShot->setCameraListener(NULL);
	}

	if (mArcSoftNightShot != NULL) {
		mArcSoftNightShot->deinit();
	}

	if (mArcSoftSceneDetection != NULL) {
		mArcSoftSceneDetection->deinit();
		mArcSoftSceneDetection->setCameraListener(NULL);
	}

	if (mArcSoftLiveEffect != NULL) {
		mArcSoftLiveEffect->deinit();
	}

	if (mArcSoftAgeGenderDetection != NULL) {
		mArcSoftAgeGenderDetection->deinit();
		mArcSoftAgeGenderDetection->setCameraListener(NULL);
	}

	if (mArcSoftPicZoom != NULL) {
		mArcSoftPicZoom->deinit();
	}
	
	mWidth = 0;
	mHeight = 0;
	mFormat = GN_IMG_FORMAT_NONE;
	mPreviewBufferSize = 0;
	mListener = NULL;

	pthread_mutex_unlock(&mMutex);
}

int32 
ArcSoftCameraFeature::
initPreviewSize(int width, int height, GNImgFormat format)
{
	MRESULT res = 0;

	pthread_mutex_lock(&mMutex);

	if (mWidth != width || mHeight != height) {
		if (mArcSoftGestureShot != NULL && (mGNCameraFeature & GN_CAMERA_FEATURE_GESTURE_SHOT)) {
			mArcSoftGestureShot->disableGestureShot();
			mArcSoftGestureShot->enableGestureShot(width, height);
		}

		if (mArcSoftSceneDetection != NULL && (mGNCameraFeature & GN_CAMERA_FEATUER_SCENE_DETECTION)) {
			mArcSoftSceneDetection->disableSceneDetection();
			mArcSoftSceneDetection->enableSceneDetection(width, height);
		}

		if (mArcSoftFaceBeauty != NULL && (mGNCameraFeature & GN_CAMERA_FEATURE_FACE_BEAUTY)) {
			mArcSoftFaceBeauty->disableFaceBeauty();
			mArcSoftFaceBeauty->enableFaceBeauty(width, height);
		}

		if (mArcSoftAgeGenderDetection != NULL && (mGNCameraFeature & GN_CAMERA_FEATUER_AGEGENDER_DETECTION)) {
			mArcSoftAgeGenderDetection->disableAgeGenderDetection();
			mArcSoftAgeGenderDetection->enableAgeGenderDetection(width, height);
		}

    }

	mFormat = format;
	mWidth  = width;
	mHeight = height;
	mPreviewData.i32Width	= width;
	mPreviewData.i32Height	= height;

	switch (format) {
		case GN_IMG_FORMAT_YV12:
			mPreviewData.u32PixelArrayFormat 	= ASVL_PAF_YV12;
			mPreviewData.pi32Pitch[0] 			= width;
			mPreviewData.pi32Pitch[1] 			= width / 2;
			mPreviewData.pi32Pitch[2] 			= width / 2;
			mPreviewBufferSize 					= width * height * 3 / 2;
			break;
		case GN_IMG_FORMAT_YUV422:
			mPreviewData.u32PixelArrayFormat 	= ASVL_PAF_YUYV;
			mPreviewData.pi32Pitch[0] 			= width * 2;
			mPreviewData.pi32Pitch[1] 			= 0;
			mPreviewData.pi32Pitch[2] 			= 0;
			mPreviewBufferSize 					= width * height * 2;
			break;
		case GN_IMG_FORMAT_NV21:
			mPreviewData.u32PixelArrayFormat 	= ASVL_PAF_NV21;
			mPreviewData.pi32Pitch[0] 			= width;
			mPreviewData.pi32Pitch[1] 			= width;
			mPreviewData.pi32Pitch[2] 			= 0;
			mPreviewBufferSize 					= width * height * 3 / 2;
			break;
		case GN_IMG_FORMAT_YUV420:
			mPreviewData.u32PixelArrayFormat 	= ASVL_PAF_I420;
			mPreviewData.pi32Pitch[0] 			= width;
			mPreviewData.pi32Pitch[1] 			= width / 2;
			mPreviewData.pi32Pitch[2] 			= width / 2;
			mPreviewBufferSize 					= width * height * 3 / 2;
			break;
		default:
			mPreviewData.u32PixelArrayFormat 	= ASVL_PAF_I420;
			mPreviewData.pi32Pitch[0] 			= width;
			mPreviewData.pi32Pitch[1] 			= width / 2;
			mPreviewData.pi32Pitch[2] 			= width / 2;
			mPreviewBufferSize 					= width * height * 3 / 2;
			break;
	}

	pthread_mutex_unlock(&mMutex);

	return 0;
}

int32 
ArcSoftCameraFeature::
setCameraListener(GNCameraFeatureListener* listener)
{
	pthread_mutex_lock(&mMutex);
	
	mListener = listener;

	if (mArcSoftSceneDetection != NULL) {
		mArcSoftSceneDetection->setCameraListener(listener);
	}

	if (mArcSoftGestureShot != NULL) {
		mArcSoftGestureShot->setCameraListener(listener);
	}

	if (mArcSoftAgeGenderDetection!= NULL) {
		mArcSoftAgeGenderDetection->setCameraListener(listener);
	}
	
	pthread_mutex_unlock(&mMutex);

	return 0;
}

int32 
ArcSoftCameraFeature::
setFaceBeauty(FaceBeautyParam const faceBeautyParam)
{
	pthread_mutex_lock(&mMutex);

	if (faceBeautyParam.faceBeautyState == GN_FACEBEAUTY_OFF) {
		mGNCameraFeature &= ~GN_CAMERA_FEATURE_FACE_BEAUTY;

		if (mArcSoftFaceBeauty != NULL) {
			mArcSoftFaceBeauty->disableFaceBeauty();
		}
	} else {
		mGNCameraFeature |= GN_CAMERA_FEATURE_FACE_BEAUTY;

		if (mArcSoftFaceBeauty != NULL) {
			mArcSoftFaceBeauty->enableFaceBeauty(mWidth, mHeight);
			mArcSoftFaceBeauty->setFaceBeautyParam(faceBeautyParam);
		}
	}

	pthread_mutex_unlock(&mMutex);
	
	return 0;
}

int32
ArcSoftCameraFeature::
setAgeGenderDetection(GNAgeGenderDetection_t const ageGenderDetection)
{
	pthread_mutex_lock(&mMutex);

	if (ageGenderDetection == GN_AGEGENDER_DETECTION_OFF) {
		mGNCameraFeature &= ~GN_CAMERA_FEATUER_AGEGENDER_DETECTION;

		if (mArcSoftAgeGenderDetection != NULL) {
			mArcSoftAgeGenderDetection->disableAgeGenderDetection();
		}
	} else {
		mGNCameraFeature |= GN_CAMERA_FEATUER_AGEGENDER_DETECTION;

		if (mArcSoftAgeGenderDetection != NULL) {
			mArcSoftAgeGenderDetection->enableAgeGenderDetection(mWidth, mHeight);
		}
	}
	
	pthread_mutex_unlock(&mMutex);

	return 0;
}

int32 
ArcSoftCameraFeature::
setGestureShot(GNGestureShot_t gestureShotMode)
{
	pthread_mutex_lock(&mMutex);
	
	if (gestureShotMode == GN_GESTURE_SHOT_OFF) {
		mGNCameraFeature &= ~GN_CAMERA_FEATURE_GESTURE_SHOT;

		if (mArcSoftGestureShot != NULL) {
			mArcSoftGestureShot->disableGestureShot();
		}
	} else {
		mGNCameraFeature |= GN_CAMERA_FEATURE_GESTURE_SHOT;

		if (mArcSoftGestureShot != NULL) {
			mArcSoftGestureShot->enableGestureShot(mWidth, mHeight);
		}
	}

	PRINTD("gestureShotMode = %d", gestureShotMode);

	pthread_mutex_unlock(&mMutex);

	return 0;
}

int32 
ArcSoftCameraFeature::
setSceneDetection(GNSceneDetection_t sceneDetectionMode)
{
	pthread_mutex_lock(&mMutex);
	
	if (sceneDetectionMode == GN_SCENE_DETECTION_OFF) {
		mGNCameraFeature &= ~GN_CAMERA_FEATUER_SCENE_DETECTION;

		if (mArcSoftSceneDetection != NULL) {
			mArcSoftSceneDetection->disableSceneDetection();
		}
	} else {
		mGNCameraFeature |= GN_CAMERA_FEATUER_SCENE_DETECTION;

		if (mArcSoftSceneDetection != NULL) {
			mArcSoftSceneDetection->enableSceneDetection(mWidth, mHeight);
		}
	}

	PRINTD("sceneDetectionMode = %d", sceneDetectionMode);

	pthread_mutex_unlock(&mMutex);
	
	return 0;
}

int32 
ArcSoftCameraFeature::
setNightShot(GNNightShot_t nightShotMode)
{
	pthread_mutex_lock(&mMutex);
	
	if (nightShotMode == GN_NIGHT_SHOT_OFF) {
		mGNCameraFeature &= ~GN_CAMERA_FEATUER_NIGHT_SHOT;

		if (mArcSoftNightShot != NULL) {
			mArcSoftNightShot->disableNightShot();
		}
	} else {
		mGNCameraFeature |= GN_CAMERA_FEATUER_NIGHT_SHOT;

		if (mArcSoftNightShot != NULL) {
			mArcSoftNightShot->enableNightShot();
		}
	}

	PRINTD("nightShotMode = %d", nightShotMode);

	pthread_mutex_unlock(&mMutex);
	
	return 0;
}

int32 
ArcSoftCameraFeature::
setEffect(GNLiveEffect_t effect)
{
	int32 res = 0;

	pthread_mutex_lock(&mMutex);

	if (mArcSoftLiveEffect != NULL) {
		if (mArcSoftLiveEffect->setLiveEffectType(effect) != 0) {
			mGNCameraFeature &= ~GN_CAMERA_FEATURE_EFFECT;
		} else {
			mGNCameraFeature |= GN_CAMERA_FEATURE_EFFECT;
		}
	}

	PRINTD("effect = %x", effect);

	pthread_mutex_unlock(&mMutex);

	return res;
}

int32 
ArcSoftCameraFeature::
setOrientation(int orientation) 
{
	pthread_mutex_lock(&mMutex);

	mOrientation = orientation;

	pthread_mutex_unlock(&mMutex);

	return 0;
}

int32 
ArcSoftCameraFeature::
setMirror(GNMirror_t mirrorMode)
{
	int32 res = 0;
	PRINTD("%s mirrorMode = %d", __func__, mirrorMode);
	if (mirrorMode != GN_MIRROR_OFF) {
		mGNCameraFeature |= GN_CAMERA_FEATUER_MIRROR;
	} else {
		mGNCameraFeature &= ~GN_CAMERA_FEATUER_MIRROR;
	}
	
	return res;
}

int32
ArcSoftCameraFeature::
setPicZoom(PicZoomParam const picZoomParam)
{
	pthread_mutex_lock(&mMutex);
	
	if (picZoomParam.picZoomMode == GN_PIC_ZOOM_OFF) {
		mGNCameraFeature &= ~GN_CAMERA_FEATURE_PIC_ZOOM;

		if (mArcSoftPicZoom!= NULL) {
			mArcSoftPicZoom->disablePicZoom();
		}
	} else {
		mGNCameraFeature |= GN_CAMERA_FEATURE_PIC_ZOOM;

		if (mArcSoftPicZoom != NULL) {
			PRINTE("%s scaleRatio = %f", __func__, picZoomParam.scaleRatio);
			mArcSoftPicZoom->enablePicZoom(picZoomParam.scaleRatio);
		}
	}

	PRINTD("picZoomMode = %d", picZoomParam.picZoomMode);

	pthread_mutex_unlock(&mMutex);
	
	return 0;

}

int32 
ArcSoftCameraFeature::
getBurstCnt(GNCameraFeature_t cameraFeature) 
{
	int32 ret = 0;

	pthread_mutex_lock(&mMutex);

	if (mArcSoftNightShot != NULL && (cameraFeature & GN_CAMERA_FEATUER_NIGHT_SHOT)) {
		ret = mArcSoftNightShot->getBurstCnt();
	}

	if (mArcSoftPicZoom != NULL && (cameraFeature & GN_CAMERA_FEATURE_PIC_ZOOM)) {
		ret = mArcSoftPicZoom->getBurstCnt();
	}
	
	pthread_mutex_unlock(&mMutex);

	return ret;
}


int32 
ArcSoftCameraFeature::
processPreview(void* inputBuffer, int size, int mask)
{
	MRESULT res = 0;

	pthread_mutex_lock(&mMutex);

	if (inputBuffer == NULL || size == 0 || size < mPreviewBufferSize) {
		PRINTE("the inputBuffer is null or invalid.");
		pthread_mutex_unlock(&mMutex); 
		return -1;
	}

	if ((mGNCameraFeature & 0XFFFF) == 0) {
		pthread_mutex_unlock(&mMutex); 
		return res;
	}
	
	mPreviewData.ppu8Plane[0] = (MByte*)inputBuffer;
	
	switch (mFormat) {
		case GN_IMG_FORMAT_YV12:
			mPreviewData.ppu8Plane[1] = mPreviewData.ppu8Plane[0] + mPreviewData.i32Width * mPreviewData.i32Height;
			mPreviewData.ppu8Plane[2] = mPreviewData.ppu8Plane[1] + mPreviewData.i32Width * mPreviewData.i32Height / 4;
			break;
		case GN_IMG_FORMAT_YUV422:
			mPreviewData.ppu8Plane[1] = NULL;
			mPreviewData.ppu8Plane[2] = NULL;
			break;
		case GN_IMG_FORMAT_NV21:
			mPreviewData.ppu8Plane[1] = mPreviewData.ppu8Plane[0] + mPreviewData.i32Width * mPreviewData.i32Height;
			mPreviewData.ppu8Plane[2] = NULL;
			break;
		case GN_IMG_FORMAT_YUV420:
			mPreviewData.ppu8Plane[1] = mPreviewData.ppu8Plane[0] + mPreviewData.i32Width * mPreviewData.i32Height;
			mPreviewData.ppu8Plane[2] = mPreviewData.ppu8Plane[1] + mPreviewData.i32Width * mPreviewData.i32Height/4;
			break;
		default:
			mPreviewData.ppu8Plane[1] = mPreviewData.ppu8Plane[0] + mPreviewData.i32Width * mPreviewData.i32Height;
			mPreviewData.ppu8Plane[2] = mPreviewData.ppu8Plane[1] + mPreviewData.i32Width * mPreviewData.i32Height/4;
			break;
	}

	if ((mGNCameraFeature & GN_CAMERA_FEATURE_GESTURE_SHOT) & mask) {
		res = processGestureShot(&mPreviewData);
		if (res != 0) {
			PRINTD("Failed to process gesture shot.");
		}
	}

	if ((mGNCameraFeature & GN_CAMERA_FEATURE_FACE_BEAUTY) & mask) {
		res = processFaceBeauty(&mPreviewData, true);
		if (res != 0) {
			PRINTD("Failed to process face beauty[#%ld].", res);
		}
	}

	if ((mGNCameraFeature & GN_CAMERA_FEATUER_SCENE_DETECTION) & mask) {
		res = processSceneDetection(&mPreviewData);
		if (res != 0) {
			PRINTD("Failed to process scene detection[#%ld].", res);
		}
	}

	if ((mGNCameraFeature & GN_CAMERA_FEATUER_AGEGENDER_DETECTION) & mask) {
		res = processAgeGenderDetection(&mPreviewData, true);
		if (res != 0) {
			PRINTD("Failed to process age gender detection[#%ld].", res);
		}
	}

	if (mDumpImage) {
		dumpImg((MUInt8*)inputBuffer, (MUInt32)size, "preview", "yuv420sp", count_dump);
		count_dump++;
	}

	pthread_mutex_unlock(&mMutex); 

	return res;
}

int32 
ArcSoftCameraFeature::
processRaw(void* inputBuffer, int size, int width, int height, GNImgFormat format, int mask)
{
	MRESULT res = 0;
	ASVLOFFSCREEN imageData;

	if (inputBuffer == NULL || size == 0 || width == 0 || height == 0) {
		PRINTE("unvalid parameters.");
		return -1;
	}

	pthread_mutex_lock(&mMutex);
	
	if ((mGNCameraFeature & (GN_CAMERA_FEATURE_FACE_BEAUTY|GN_CAMERA_FEATUER_NIGHT_SHOT
		| GN_CAMERA_FEATURE_EFFECT | GN_CAMERA_FEATUER_AGEGENDER_DETECTION
		| GN_CAMERA_FEATURE_PIC_ZOOM)) == 0) {
		pthread_mutex_unlock(&mMutex); 
		return res;
	}

	if (ALIGN_FORMAT != ALIGN_TO_32) {
		width = ALIGN_TO_SIZE(width, ALIGN_FORMAT);
		height = ALIGN_TO_SIZE(height, ALIGN_FORMAT);
	}

	imageData.i32Width	= width;
	imageData.i32Height = height;
	PRINTE("%s width %d height %d size %d", __func__, width, height, size);
	switch (format) {
		case GN_IMG_FORMAT_YV12:
			imageData.u32PixelArrayFormat = ASVL_PAF_YV12;
			imageData.pi32Pitch[0] = width;
			imageData.pi32Pitch[1] = width / 2;
			imageData.pi32Pitch[2] = width / 2;
			imageData.ppu8Plane[0] = (MByte*)inputBuffer;
			imageData.ppu8Plane[1] = imageData.ppu8Plane[0] + imageData.i32Width * imageData.i32Height;
			imageData.ppu8Plane[2] = imageData.ppu8Plane[1] + imageData.i32Width * imageData.i32Height / 4;
			break;
		case GN_IMG_FORMAT_YUYV:
			imageData.u32PixelArrayFormat = ASVL_PAF_YUYV;
			imageData.pi32Pitch[0] = width * 2;
			imageData.pi32Pitch[1] = 0;
			imageData.pi32Pitch[2] = 0;
			imageData.ppu8Plane[0] = (MByte*)inputBuffer;
			imageData.ppu8Plane[1] = NULL;
			imageData.ppu8Plane[2] = NULL;
			break;
		case GN_IMG_FORMAT_NV21:
			imageData.u32PixelArrayFormat = ASVL_PAF_NV21;
			imageData.pi32Pitch[0] = width;
			imageData.pi32Pitch[1] = width;
			imageData.pi32Pitch[2] = 0;
			imageData.ppu8Plane[0] = (MByte*)inputBuffer;
			imageData.ppu8Plane[1] = imageData.ppu8Plane[0] + imageData.i32Width * imageData.i32Height;
			imageData.ppu8Plane[2] = NULL;
			break;
		default:
			imageData.u32PixelArrayFormat = ASVL_PAF_YUYV;
			imageData.pi32Pitch[0] = width * 2;
			imageData.pi32Pitch[1] = 0;
			imageData.pi32Pitch[2] = 0;
			imageData.ppu8Plane[0] = (MByte*)inputBuffer;
			imageData.ppu8Plane[1] = NULL;
			imageData.ppu8Plane[2] = NULL;
			break;
	}

	//process night shot
	if ((mGNCameraFeature & GN_CAMERA_FEATUER_NIGHT_SHOT) & mask) {
		res = processNightShot(&imageData);
		if (res != 0) {
			PRINTE("Failed to process night shot");
		}
	}

	//process age gender detection
	if ((mGNCameraFeature & GN_CAMERA_FEATUER_AGEGENDER_DETECTION) & mask) {
		res = processAgeGenderDetection(&imageData, false);
		if (res != 0) {
			PRINTE("Failed to process age gender detection.");
		}
	}

	//process face beauty
	if ((mGNCameraFeature & GN_CAMERA_FEATURE_FACE_BEAUTY) & mask) {
		res = processFaceBeauty(&imageData, false);
		if (res != 0) {
			PRINTE("Failed to process face beauty.");
		}
	}

	//process live effect
	if ((mGNCameraFeature & GN_CAMERA_FEATURE_EFFECT) & mask) {
		res = processLiveEffect(&imageData, mGNCameraFeature & GN_CAMERA_FEATUER_MIRROR);
		if (res != 0) {
			PRINTE("Failed to process live effect.");
		}
	}

	//process pic zoom
	if ((mGNCameraFeature & GN_CAMERA_FEATURE_PIC_ZOOM) & mask) {
		res = processPicZoom(&imageData);
		if (res != 0) {
			PRINTE("Failed to process night shot");
		}
	}

	if (mDumpImage) {
		dumpImg((MUInt8*)inputBuffer, (MUInt32)size, "raw", "yuv", count_dump);
		count_dump++;
	}

	pthread_mutex_unlock(&mMutex); 
	
	return res;
}

int32 
ArcSoftCameraFeature::
processFaceBeauty(LPASVLOFFSCREEN param, bool isPreview)
{
	MRESULT res = 0;

	if (mArcSoftFaceBeauty != NULL) {
		res = mArcSoftFaceBeauty->processFaceBeauty(param, isPreview);
	}
	
	return res;
}

int32
ArcSoftCameraFeature::
processAgeGenderDetection(LPASVLOFFSCREEN param, bool isPreview)
{
	MRESULT res = 0;

	if (mArcSoftAgeGenderDetection != NULL) {
		res = mArcSoftAgeGenderDetection->processAgeGenderDetection(param, isPreview);
	}

	return res;
}

int32 
ArcSoftCameraFeature::
processGestureShot(LPASVLOFFSCREEN param)
{
	MRESULT res = 0;
	
	if (mArcSoftGestureShot != NULL) {
		res = mArcSoftGestureShot->processGestureShot(param);
	}

	return res;
}

int32 
ArcSoftCameraFeature::
processSceneDetection(LPASVLOFFSCREEN param)
{
	MRESULT res = 0;

	if (mArcSoftSceneDetection != NULL) {
		res = mArcSoftSceneDetection->processSceneDetection(param);
		if (res != 0) {
			PRINTE("Failed to process scene detection [#%ld].", res);
		}
	}

	return res;
}

int32 
ArcSoftCameraFeature::
processNightShot(LPASVLOFFSCREEN param)
{
	MRESULT res = 0;

	if (mArcSoftNightShot != NULL) {
		res = mArcSoftNightShot->processNightShot(param);
		if (res != 0) {
			PRINTE("Failed to process night shot [#%ld].", res);
		}
	}

	return res;
}

int32 
ArcSoftCameraFeature::
processLiveEffect(LPASVLOFFSCREEN param, bool isMirror)
{
	MRESULT res = 0;

	if (mArcSoftLiveEffect!= NULL) {
		res = mArcSoftLiveEffect->processLiveEffect(param, isMirror);
		if (res != 0) {
			PRINTE("Failed to process live effect [#%ld].", res);
		}
	}

	return res;
}

int32
ArcSoftCameraFeature::
processPicZoom(LPASVLOFFSCREEN param)
{
	MRESULT res = 0;
	
	if (mArcSoftPicZoom!= NULL) {
		res = mArcSoftPicZoom->processPicZoom(param);
		if (res != 0) {
			PRINTE("Failed to process night shot [#%ld].", res);
		}
	}

	return res;
}

bool 
ArcSoftCameraFeature::
dumpImg(MUInt8 *addr, MUInt32 size, char const * const tag, char const * const filetype, int filenum)
{
    
	char fileName[64] = {0};
    
    sprintf(fileName, "/data/%s_%d.%s", tag, filenum, filetype);
	
    FILE* fp = fopen(fileName, "w");
    if (NULL == fp)
    {
        PRINTE("fail to open file to save img: %s", fileName);
        return false;
    }
    
    fwrite(addr, 1, size, fp);
    fclose(fp);

    return true;
}

};
