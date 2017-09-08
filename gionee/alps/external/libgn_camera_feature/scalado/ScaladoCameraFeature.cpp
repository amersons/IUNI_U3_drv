/*************************************************************************************
 * 
 * Description:
 * 	Defines scalado APIs for camera hal.
 *
 * Author : wutangzhi
 * Email  : wutz@gionee.com
 * Date   : 2012-06-11
 *
 *************************************************************************************/
 
#include "scbdefs.h"
#include "caps_base.h"
#include "ctstream_buffer.h"
#include "fm_exif.h"
#include "fm_photoart.h"
#include "oslfile.h"
#include "oslmem.h"
#include "fm_clearshot.h"
#include "fm_face.h"
#include "ctfacedetector_standard.h"
#include "ctfacecollection.h"
#include "ScaladoCameraFeature.h"
#include "ScaladoCameraFeatureDefs.h"

#define max_preview_width 800
#define max_preview_height 480

namespace android {

ScaladoCameraFeature::
ScaladoCameraFeature() :
	mScaladoHdrLowlight(),
	mScaladoPictureFrame(),
	mScaladoPanorama(),
	mInputImage(NULL),
	mOutImage(NULL),
	mSession(NULL),
	mListener(NULL),
	mOrientation(0),
	mEffectStyle(GN_LIVE_EFFECT_NONE),
	mGNCameraFeature(GN_CAMERA_FEATURE_NONE),
	mCameraType(GN_CAMERA_TYPE_FRONT),
	mPreviewBufferSize(0),
	mFormat(GN_IMG_FORMAT_NONE)
{	
	mPreviewSize.w = max_preview_width;
	mPreviewSize.h = max_preview_height;

	::memset(mFilePath, 0, sizeof(mFilePath));
	::memset(mFrameName, 0, sizeof(mFrameName));

	pthread_mutex_init(&mMutex, NULL);   
}

ScaladoCameraFeature::
~ScaladoCameraFeature() 
{
	pthread_mutex_destroy(&mMutex);  
}


ScaladoCameraFeature*
ScaladoCameraFeature::createInstance() 
{
	return new ScaladoCameraFeature();
}

void
ScaladoCameraFeature::destroyInstance() 
{
	delete this;
}

void 
ScaladoCameraFeature::
setCameraType(GNCameraType_t cameraType) 
{
	mCameraType = cameraType;
}

int32 
ScaladoCameraFeature::
setCameraListener(GNCameraFeatureListener* listener) 
{
	int32 res = 0;

	mListener = listener;

	return res;
}

int32
ScaladoCameraFeature::
setCapturePath(const char* filePath)
{
	int32 res = 0;

	::memcpy(mFilePath, filePath, sizeof(mFilePath));

	return res;
}

int32
ScaladoCameraFeature::
init()
{
	int32 res = 0;

	return res;
}

void 
ScaladoCameraFeature::
deinit()
{
	PRINTD("ScaladoCameraFeature::deinit() E");

	pthread_mutex_lock(&mMutex);
	
	mScaladoHdrLowlight.deinit();
	mScaladoPictureFrame.deinit();
	mScaladoPanorama.deinit();
	
	if(mInputImage != NULL) {
		caps_destroyImage(mInputImage);
	}

	if(mOutImage != NULL) {
		caps_destroyImage(mOutImage);
	}

	if(mSession != NULL) {
		caps_destroySession(mSession);
	}

	::memset(mFilePath, 0, sizeof(mFilePath));

	mInputImage = NULL;
	mOutImage = NULL;
	mSession = NULL;	
	mGNCameraFeature = 0;
	pthread_mutex_unlock(&mMutex);

	PRINTD("ScaladoCameraFeature::deinit() X");
}

int32 
ScaladoCameraFeature::
setEffect(GNLiveEffect_t effect)
{
	int32 res = 0;
	
	if (effect != GN_LIVE_EFFECT_NONE) {
		if ((mGNCameraFeature & (~(GN_CAMERA_FEATURE_EFFECT|GN_CAMERA_FEATURE_PICTURE_FREAME
				|GN_CAMERA_FEATUER_MIRROR))) != 0) {
			PRINTE("failed to set live effect!");
			res = -1;
		} else {
			mEffectStyle = effect;
			mGNCameraFeature |= GN_CAMERA_FEATURE_EFFECT;
		}
	} else {
		mEffectStyle = effect;
		mGNCameraFeature &= ~GN_CAMERA_FEATURE_EFFECT;
	}

	return res;
}

int32 
ScaladoCameraFeature::
setPictureFrame(char* frameName)
{
	int32 res = 0;

	if (frameName != NULL) {
		if ((mGNCameraFeature & (~(GN_CAMERA_FEATURE_PICTURE_FREAME|GN_CAMERA_FEATURE_EFFECT
			| GN_CAMERA_FEATUER_MIRROR))) != 0) {
			PRINTE("failed to set picture frame!");
			res = -1;
		} else {
			mGNCameraFeature |= GN_CAMERA_FEATURE_PICTURE_FREAME;
			::memset(mFrameName, 0, sizeof(mFrameName));
			sprintf(mFrameName, "%s", frameName);
		}
	} else {
		mGNCameraFeature &= ~GN_CAMERA_FEATURE_PICTURE_FREAME;
		::memset(mFrameName, 0, sizeof(mFrameName));
	}

	return res;
}

int32 
ScaladoCameraFeature::
setHdr(GNHdr_t hdrMode)
{
	int32 res = 0;

	if (hdrMode != GN_HDR_OFF) {
		if ((mGNCameraFeature & (~GN_CAMERA_FEATURE_HDR)) != 0) {
			PRINTE("failed to set HDR!");
			res = -1;
		} else {
			mGNCameraFeature |= GN_CAMERA_FEATURE_HDR;
		}
	} else {
		mGNCameraFeature &= ~GN_CAMERA_FEATURE_HDR;
	}
	
	return res;
}

int32 
ScaladoCameraFeature::
setLowlight(GNLowlight_t lowlightMode)
{
	int32 res = 0;

	if (lowlightMode != GN_LOWLIGHT_OFF) {
		if ((mGNCameraFeature & (~GN_CAMERA_FEATURE_LOWLIGHT)) != 0) {
			PRINTE("failed to set Lowlight!");
			res = -1;
		} else {
			mGNCameraFeature |= GN_CAMERA_FEATURE_LOWLIGHT;
		}
	} else {
		mGNCameraFeature &= ~GN_CAMERA_FEATURE_LOWLIGHT;
	}

	return res;
}

int32 
ScaladoCameraFeature::
setBurstCnt(GNCameraFeature_t cameraFeature, int count) 
{
	int32 res = 0;

	if (cameraFeature == GN_CAMERA_FEATURE_HDR) {
		mScaladoHdrLowlight.setHDRBurstCnt(count);
	} else if (cameraFeature == GN_CAMERA_FEATURE_LOWLIGHT) {
		mScaladoHdrLowlight.setLowlightBurstCnt(count);
	} 

	return res;
}

int32 
ScaladoCameraFeature::
setOrientation(int orientation)
{
	int32 res = 0;
	
	mOrientation = orientation;
	
	return res;
}

int32 
ScaladoCameraFeature::
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
ScaladoCameraFeature::
initPreviewSize(int width, int height, GNImgFormat format)
{
	CRESULT res = CERR_OK;
	CTColormode colorMode = CM_UNDEFINED;
	CTuint32 scanline = 0;
	
	pthread_mutex_lock(&mMutex);

	mPreviewSize.w = width;
	mPreviewSize.h = height;
	mPreviewBufferSize = width * height * 3 / 2; //only support for YUV420
	mFormat = format;

	if(mInputImage != NULL) {
		caps_destroyImage(mInputImage);
		mInputImage = NULL;
	}

	colorMode = mapPixelFormatToScalado(format);
	scanline = (caps_pixelBitSize(colorMode) * width + 7) / 8;

	if((res = caps_createImage(0, mPreviewSize, scanline, colorMode, &mInputImage)) != CERR_OK) {
	   PRINTE_RES("create input image fail", res);
	   
	   pthread_mutex_unlock(&mMutex);
	   return (int32)res;
	}

	if (mOutImage != NULL) {
		caps_destroyImage(mOutImage);
		mOutImage = NULL;
	}

	if((res = caps_createImage(0, mPreviewSize, scanline, colorMode, &mOutImage)) != CERR_OK ) {
	   	PRINTE_RES("create out image fail", res);
		
		caps_destroyImage(mInputImage);
		mInputImage = NULL;

		pthread_mutex_unlock(&mMutex);
		
		return (int32)res;
	}

	if(mSession != NULL) {
		caps_destroySession( mSession );
		
		mSession=NULL;
	}

	mInputImage->scanline = scanline;
	mInputImage->dims.w = width;
	mInputImage->dims.h = height;

	mOutImage->scanline = scanline;
	mOutImage->dims.w = width;
	mOutImage->dims.h = height;

	pthread_mutex_unlock(&mMutex);
	
	return (res == CERR_OK) ? 0 : (int32)res;
}

int32 
ScaladoCameraFeature::
processPreview(void* inputBuffer, int size, int mask)
{
	CRESULT res = CERR_OK;
	int ySize = 0;
	int uSize = 0;
	int vSize = 0;

	if ((mask & mGNCameraFeature) == 0) {
		return 0;
	}
	
	if ((mGNCameraFeature & (GN_CAMERA_FEATURE_EFFECT | GN_CAMERA_FEATURE_PANORAMA
			| GN_CAMERA_FEATUER_MIRROR)) == 0) {
		return 0;
	}

	if(mInputImage == NULL) {
		PRINTE("mInputImage is NULL ");
		return (int32)CERR_OPERATION_FAILED;
	}

	pthread_mutex_lock(&mMutex);

	if (inputBuffer == NULL || size == 0 || size < mPreviewBufferSize) {
		PRINTE("inputBuffer is invalid.");
		pthread_mutex_unlock(&mMutex);
		return (int32)CERR_OPERATION_FAILED;;
	}

	if (mFormat == GN_IMG_FORMAT_YV12) {
		ySize = mInputImage->dims.w * mInputImage->dims.h;
		uSize = mInputImage->dims.w * mInputImage->dims.h / 4;
		vSize = uSize;

		//copy Y buffer to mInputImage
		memcpy(mInputImage->pixels->data, inputBuffer, ySize);	
		//copy V buffer to mInputImage
		memcpy(mInputImage->pixels->data + ySize, inputBuffer + ySize + uSize, vSize); 	
		//copy U buffer to mInputImage
		memcpy(mInputImage->pixels->data + ySize + vSize, inputBuffer + ySize, uSize);  
	} else {
		memcpy(mInputImage->pixels->data, inputBuffer, mInputImage->pixels->size);
	}
	
	if(mSession == NULL) {
		if((res = caps_newSessionWithRaw(mInputImage, &mSession)) != CERR_OK) {
		   PRINTE_RES("Failed to create Session", res);
		   pthread_mutex_unlock(&mMutex); 
		   return (int32)res;
		} 
	}

	if ((mGNCameraFeature & GN_CAMERA_FEATURE_PANORAMA) & mask) {
		res = caps_setSourceImageRaw(mSession,mInputImage);
		if (res == CERR_OK) {
			res = mScaladoPanorama.track(mSession);
			if (res != CERR_OK) {
				PRINTE("failed to track panorama");
			}
		} else {
			PRINTE("caps_setSourceImageRaw failed");
		}
	} 

	if ((mGNCameraFeature & GN_CAMERA_FEATURE_EFFECT) & mask) {
		if ((res = caps_setSourceImageRaw(mSession,mInputImage)) == CERR_OK) {
			caps_signalSessionEvent(mSession, EVENT_SOURCEDATA_CHANGE);    
			caps_undoAll(mSession);

			if ((res = applyEffect(mSession, mPreviewSize)) == CERR_OK) {
				res = caps_renderAsRawToBuffer(mSession, mOutImage, CAPS_OUTPUT_PRESERVE_AR, 0);
				if (res == CERR_OK) {
					if (mFormat == GN_IMG_FORMAT_YV12) {
						//copy Y buffer to inputBuffer
						memcpy(inputBuffer, mOutImage->pixels->data, ySize);
						//copy U buffer to inputBuffer
						memcpy(inputBuffer + ySize, mOutImage->pixels->data + ySize + vSize, uSize); 
						//copy V buffer to inputBuffer
						memcpy(inputBuffer + ySize + vSize, mOutImage->pixels->data + ySize, vSize); 
					} else {
						memcpy(inputBuffer,mOutImage->pixels->data, mOutImage->pixels->size);
					}
				}
			}
		}
	}
	
	pthread_mutex_unlock(&mMutex); 

	return (res == CERR_OK) ? 0 : (int32)res;
}

int32 
ScaladoCameraFeature::
processPicture(void* inputBuffer, int* size, int mask)
{
	CRESULT res = CERR_OK;
	CTSession jpegSession;
	CTBuffer jpegBuffer;
	CTBuffer* outputBuffer = NULL;
	CTStream* inputBufferStream=NULL;
	CTStream* outputBufferStream = NULL;
	CTuint32 maxBuffer = 0;
	CTSize jpegSize = {0, 0};
	CTExifSession exifSession = NULL;
	CTColormode rawColorMode = CM_YUV420P; 
	int scanline = 0;
	int tmpDataLen = 0;
	CTBuffer* rawBuffer = NULL;
	CTImage* rawImage = NULL;
	CTSession rawSession = NULL;

	PRINTD("ScaladoCameraFeature::processPicture() E");

	if ((mask & mGNCameraFeature) == 0) {
		return 0;
	}

	if (mGNCameraFeature == GN_CAMERA_FEATURE_NONE) {
		return 0;
	}

	pthread_mutex_lock(&mMutex);

	jpegBuffer.size = *size;
	jpegBuffer.data = (CTuint8*)inputBuffer;

	exif_newSessionWithBuffer(&jpegBuffer, &exifSession);

	res = caps_createBuffer(maxBuffer, &outputBuffer);
	if (res != CERR_OK) {
		PRINTE_RES("Failed to create buffer", res);
		goto EXIT;
	}

	res = ctstream_createBufferStream(&jpegBuffer, maxBuffer, &inputBufferStream);
	if (res != CERR_OK) {
		PRINTE_RES("Failed to create input buffer stream", res);	
		goto EXIT;
	}
	
	res = ctstream_createBufferStream(outputBuffer, maxBuffer, &outputBufferStream);
	if (res != CERR_OK) {
		PRINTE_RES("Failed to create output buffer stream", res);		
		goto EXIT;
	}
	
	res = caps_createSession(inputBufferStream, IMAGE_FORMAT_JPEG, &jpegSession);
	if(res != CERR_OK) {
		PRINTE_RES("caps_createSession fail", res);
		goto EXIT;
	}

	res = caps_getSourceImageSize(jpegSession, &jpegSize);
	if(res != CERR_OK) {
		PRINTE_RES("caps_getSourceImageSize fail", res);
		goto EXIT;
	}

	scanline = (caps_pixelBitSize(rawColorMode) * jpegSize.w + 7) / 8;
	res = caps_createBuffer(jpegSize.h * scanline, &rawBuffer);
	if(res != CERR_OK) {
		PRINTE_RES("caps_createBuffer fail", res);
		goto EXIT;
	}

	res = caps_createImage(rawBuffer, jpegSize, scanline, rawColorMode, &rawImage);
	if(res != CERR_OK) {
		PRINTE_RES("caps_createImage fail", res);
		goto EXIT;
	}

	res = caps_newSessionWithRaw(rawImage, &rawSession);
	if(res != CERR_OK) {
		PRINTE_RES("caps_newSessionWithRaw fail", res);
		goto EXIT;
	}

	res = caps_renderAsRawToBuffer(jpegSession, rawImage, CAPS_OUTPUT_PRESERVE_AR, 0);
	if(res != CERR_OK) {
		PRINTE_RES("caps_renderAsRawToBuffer fail", res);
		goto EXIT;
	}

	if ((mGNCameraFeature & GN_CAMERA_FEATURE_HDR) & mask) {
		res = applyHDR(rawSession, outputBufferStream, exifSession);
	} 

	if ((mGNCameraFeature & GN_CAMERA_FEATURE_LOWLIGHT) & mask) {
		res = applyLowlight(rawSession, outputBufferStream, exifSession);
	} 

	if ((mGNCameraFeature & GN_CAMERA_FEATURE_PANORAMA) & mask) {
		res = applyAUTORAMA(rawSession, exifSession);
		goto EXIT;
	} 
	
	if ((mGNCameraFeature & GN_CAMERA_FEATURE_PICTURE_FREAME) & mask) {
		res = applyPictureFrame(rawSession);
		
		if (res == CERR_OK) {
			exif_addExifHeaderFromSession(rawSession, exifSession);
			res = caps_render(rawSession, outputBufferStream, jpegSize,
				CAPS_OUTPUT_PRESERVE_AR, IMAGE_FORMAT_JPEG, 0);
		}
	} 

	if ((mGNCameraFeature & GN_CAMERA_FEATURE_EFFECT) & mask) {
		res = applyEffect(rawSession, jpegSize);

		if (res == CERR_OK) {
			exif_addExifHeaderFromSession(rawSession, exifSession);
			res = caps_render(rawSession, outputBufferStream, jpegSize,
				CAPS_OUTPUT_PRESERVE_AR, IMAGE_FORMAT_JPEG, 0);
		}
	} 
		
	if(res != CERR_OK) {
		PRINTE_RES("caps_render fail", res);
    } else {
		*size = outputBuffer->size;
		memcpy(inputBuffer, outputBuffer->data, outputBuffer->size);
				
#ifdef DEBUG_DUMP
		dump(rawSession, jpegSize);
#endif
	}

EXIT:
	if (jpegSession != NULL) {
		caps_destroySession(jpegSession);
		jpegSession = NULL;
	}

	if (jpegSession != NULL) {
		ctstream_destroy(outputBufferStream);
		outputBufferStream = NULL;
	}

	if (inputBufferStream != NULL) {
		ctstream_destroy(inputBufferStream); 
		inputBufferStream = NULL;
	}

	if (outputBuffer != NULL) {
	    caps_destroyBuffer(outputBuffer);
		outputBuffer = NULL;
	}

	if(exifSession != NULL) {
		res = exif_destroySession(exifSession);
		exifSession = NULL;
	}

	if (rawSession) {
		caps_destroySession(rawSession);
	}

	if(rawImage) {
		caps_destroyImage(rawImage);
	}

	pthread_mutex_unlock(&mMutex);
	
	PRINTD("ScaladoCameraFeature::processPicture() X");

    return (res == CERR_OK) ? 0 : (int32)res;
}

int32 
ScaladoCameraFeature::
processRaw(void* inputBuffer, int size, int width, int height, GNImgFormat format, int mask) 
{
	CRESULT res = CERR_OK;
	CTColormode colorMode = CM_UNDEFINED;
	CTImage* inputImage = NULL;
	CTImage* outImage = NULL;
	CTSession rawSession;
	CTSize rawSize = {0, 0};
	CTuint32 scanline = 0;

	PRINTD("ScaladoCameraFeature::processRaw() E");

	if ((mask & mGNCameraFeature) == 0) {
		return res;
	}

	if ((mGNCameraFeature & (GN_CAMERA_FEATURE_EFFECT | GN_CAMERA_FEATURE_PICTURE_FREAME 
		| GN_CAMERA_FEATUER_MIRROR)) == 0) {
		return res;
	}

	pthread_mutex_lock(&mMutex); 

	rawSize.w = width;
	rawSize.h = height;
	colorMode = mapPixelFormatToScalado(format);
	scanline = (caps_pixelBitSize(colorMode) * width + 7) / 8;

	if((res = caps_createImage(0, rawSize, scanline, colorMode, &inputImage)) != CERR_OK) {
	   PRINTE_RES("create input image fail", res);
	   pthread_mutex_unlock(&mMutex);
	   return (int32)res;
	}

	if((res = caps_createImage(0, rawSize, scanline, colorMode, &outImage)) != CERR_OK) {
	   PRINTE_RES("create out image fail",res);
	   goto EXIT_OUTIMG;
	}

	if (copyBuffer(&inputImage->pixels->data[0], inputBuffer, size, width, height, colorMode, true) != CERR_OK) {
		PRINTE("Failed to copy buffer!");
		goto EXIT_SESSION;
	}

	if((res = caps_newSessionWithRaw(inputImage, &rawSession)) != CERR_OK) {
	   PRINTE_RES("Failed to create Session", res);
	   goto EXIT_SESSION;
	}
	
	if ((mGNCameraFeature & GN_CAMERA_FEATURE_EFFECT) & mask) {
		res = applyEffect(rawSession, rawSize);
	} 

	if ((mGNCameraFeature & GN_CAMERA_FEATURE_PICTURE_FREAME) & mask) {
		res = applyPictureFrame(rawSession);
	} 

	if ((mGNCameraFeature & GN_CAMERA_FEATUER_MIRROR) & mask) {
		res = applyMirror(rawSession, rawSize);
	}

	if(res != CERR_OK) {
		PRINTE_RES("caps_renderAsRawToBuffer fail", res);
	} else {
		res = caps_renderAsRawToBuffer(rawSession, outImage, CAPS_OUTPUT_PRESERVE_AR, 0);
		if (res == CERR_OK) {
			if (copyBuffer(inputBuffer, &outImage->pixels->data[0], size, width, height, colorMode, false) != CERR_OK) {
				PRINTE("Failed to copy buffer!");
			}
		}
	}

#ifdef DEBUG_DUMP
	dump(rawSession, rawSize);
#endif
	
	caps_destroySession(rawSession);
	rawSession = NULL;

EXIT_SESSION:
	caps_destroyImage(outImage);
	outImage = NULL;

EXIT_OUTIMG:
	caps_destroyImage(inputImage);
	inputImage = NULL;

	pthread_mutex_unlock(&mMutex);

	PRINTD("ScaladoCameraFeature::processRaw() X");
	
	return (res == CERR_OK) ? 0 : (int32)res;
}

int32 
ScaladoCameraFeature::
startAUTORAMA(int32 num)
{
	int32 res = 0;

	if ((mGNCameraFeature & (~GN_CAMERA_FEATURE_PANORAMA)) != 0) {
		PRINTE("failed to set AUTORAMA!");
		res = -1;
	} else {
		mGNCameraFeature |= GN_CAMERA_FEATURE_PANORAMA;
		mScaladoPanorama.setListener(mListener);
		mScaladoPanorama.setCapturePath(mFilePath);
		mScaladoPanorama.startAUTORAMA(num);
	}
	
	return (res == CERR_OK) ? 0 : (int32)res;
}

int32 
ScaladoCameraFeature::
stopAUTORAMA(int32 isMerge)
{
	CRESULT res = CERR_OK;

	mScaladoPanorama.stopAUTORAMA(isMerge);
	mScaladoPanorama.setListener(NULL);
	mGNCameraFeature &= ~GN_CAMERA_FEATURE_PANORAMA;

	return (res == CERR_OK) ? 0 : (int32)res;
}

CRESULT 
ScaladoCameraFeature::
applyEffect(CTSession session, CTSize size)
{
	CRESULT res = CERR_OK;
	
	res = mScaladoLiveEffect.setScaladoLiveEffect(session, mEffectStyle, size.w, size.h);
	
	return res;
}

CRESULT 
ScaladoCameraFeature::
applyPictureFrame(CTSession session)
{
	CRESULT res = CERR_OK;

	if ((mGNCameraFeature & GN_CAMERA_FEATUER_MIRROR) && (mCameraType == GN_CAMERA_TYPE_FRONT)) {
		res = mScaladoPictureFrame.renderPictureFrameImage(session, mFrameName, GN_CAMERA_TYPE_BACK, mOrientation);
	} else {
		res = mScaladoPictureFrame.renderPictureFrameImage(session, mFrameName, mCameraType, mOrientation);
	}
	
	return res;
}

CRESULT 
ScaladoCameraFeature::
applyHDR(CTSession session, CTStream* outputStream, CTExifSession exif)
{
	CRESULT res = CERR_OK;

	res = mScaladoHdrLowlight.addHDRImage(session, outputStream, exif);
	//if (mScaladoHdrLowlight.getImageCounter() == HDR_BURST_CNT) {
	//	mScaladoHdrLowlight.addExif(exif);
	//	res = mScaladoHdrLowlight.renderHDRImage(outputsteam);
	//}

	return res;
}

CRESULT 
ScaladoCameraFeature::
applyLowlight(CTSession session, CTStream* outputStream, CTExifSession exif)
{
	CRESULT res = CERR_OK;

	res = mScaladoHdrLowlight.addLowlightImage(session, outputStream, exif);
	//if (mScaladoHdrLowlight.getImageCounter() == LOWLIGHT_BURST_CNT) {
	//	mScaladoHdrLowlight.addExif(exif);
	//	res = mScaladoHdrLowlight.renderLowlightImage(outputsteam);
	//}
	
	return res;
}

CRESULT
ScaladoCameraFeature::
applyAUTORAMA(CTSession session, CTExifSession exif) 
{
	CRESULT res = CERR_OK;
	
	res =  mScaladoPanorama.addImage(session, exif);

	return res;
}

CRESULT 
ScaladoCameraFeature::
applyMirror(CTSession session, CTSize size)
{
	CRESULT res = CERR_OK;
	
	res = mScaladoLiveEffect.setScaladoLiveEffect(session, GN_LIVE_EFFECT_FLIP, size.w, size.h);
	
	return res;
}


CTColormode 
ScaladoCameraFeature::
mapPixelFormatToScalado(GNImgFormat format) {
	CTColormode colorMode = CM_UNDEFINED;

	if (format == GN_IMG_FORMAT_YUV420P) {
		colorMode = CM_YUV420P; 
    } else if (format == GN_IMG_FORMAT_YUV420SP) {
        colorMode = CM_YUV420SP;
    } else if (format == GN_IMG_FORMAT_RGBA8888) {
        colorMode = CM_RGBA8888;
    } else if (format == GN_IMG_FORMAT_YUV422) {
		colorMode = CM_YUV422;
	} else if (format == GN_IMG_FORMAT_YUYV) {
		colorMode = CM_YUV422_Y1UY2V;
	} else if (format == GN_IMG_FORMAT_NV21) {
		colorMode = CM_YVU420SP;
	} else if (format == GN_IMG_FORMAT_YV12) {
        colorMode = CM_YUV420P;
	}

	return colorMode;
}

CRESULT 
ScaladoCameraFeature::
copyBuffer(void* dst, void* src, int size, int width, int height, CTColormode format, bool isCopyIn)
{
	CRESULT res = CERR_OK;
	int stride = 0;
	int scanline = 0;
	int num_planes = 0;
	GNCamOffset offset[2] = {0};
	int i = 0;
	int j = 0;
	void* temp = NULL;

	if ((ALIGN_FORMAT == ALIGN_TO_32) || ((width % ALIGN_FORMAT == 0) && (height % ALIGN_FORMAT == 0))) {
		memcpy(dst, src, size);
		return res;
	} 

	stride = ALIGN_TO_SIZE(width, ALIGN_FORMAT);
	scanline = ALIGN_TO_SIZE(height, ALIGN_FORMAT);

	switch (format) {
		case CM_YVU420SP:
		case CM_YUV420P:
			num_planes = 2;
			offset[0].width 	= width;
			offset[0].height	= height;
			offset[0].stride	= stride;
			offset[0].scanline	= scanline;
			offset[0].len		= ALIGN_TO_SIZE(offset[0].scanline * offset[0].stride, ALIGN_FORMAT);
			
			offset[1].width 	= width;
			offset[1].height	= height / 2;
			offset[1].stride	= stride;
			offset[1].scanline	= scanline / 2;
			offset[1].len		= ALIGN_TO_SIZE(offset[1].scanline * offset[1].stride, ALIGN_FORMAT);
			break;
		default:
			PRINTE("Unsupport format and failed to copy buffer!");
			res = CERR_OPERATION_FAILED;
			return res;
	}

	if (isCopyIn) {
		
		for (i = 0; i < num_planes; i++) {
			if (i > 0) {
				temp = src + offset[i - 1].len;
			} else {
				temp = src;
			}
			
			for (j = 0; j < offset[i].height; j++) {
				memcpy(dst, temp, offset[i].width);
				dst += offset[i].width;
				temp += offset[i].stride;
			}
		}
	} else {
		for (i = 0; i < num_planes; i++) {
			if (i > 0) {
				temp = dst + offset[i - 1].len;
			} else {
				temp = dst;
			}
			
			for (j = 0; j < offset[i].height; j++) {
				memcpy(temp, src, offset[i].width);
				temp += offset[i].stride;
				src += offset[i].width;
			}
		}
	}

	return res;
}

void
ScaladoCameraFeature::
dump(CTSession session, CTSize size)
{
	CRESULT res = CERR_OK;
	const DCHAR* filename = "/data/scalado_test.jpeg";
#if 1
	res = caps_renderToFile(session, filename, size,
			CAPS_OUTPUT_PRESERVE_AR, IMAGE_FORMAT_JPEG, 0);
	if (res != CERR_OK) {
		PRINTE_RES("Failed to render to file", res);
	}
#else

	CTBuffer* frameBuffer = NULL;
	CTSession rawSession = NULL;
	CTImage* image = NULL;
	int scanline = 0;
	CTBuffer* buffer = NULL;

	scanline = (caps_pixelBitSize(CM_RGBA8888) * size.w + 7) / 8;
	res = caps_createBuffer(size.h * scanline, &buffer);
	if(res != CERR_OK) {
		PRINTE_RES("caps_createBuffer fail", res);
		goto EXIT;
	}

	res = caps_createImage(buffer, size, scanline, CM_RGBA8888, &image);
	if(res != CERR_OK) {
		PRINTE_RES("caps_createImage fail", res);
		goto EXIT;
	}

	res = caps_renderAsRawToBuffer(session, image, CAPS_OUTPUT_PRESERVE_AR, 0);
	if(res != CERR_OK) {
		PRINTE_RES("caps_renderAsRawToBuffer fail", res);
		goto EXIT;
	}

	res = caps_newSessionWithRaw(image, &rawSession);
	if (res != CERR_OK) {
		PRINTE_RES("caps_newSessionWithRaw fail", res);
		goto EXIT;
	}
	
	res = caps_renderToFile(session, filename, size,
			CAPS_OUTPUT_PRESERVE_AR, IMAGE_FORMAT_JPEG, 0);
	if (res != CERR_OK) {
		PRINTE_RES("Failed to render to file", res);
	}
EXIT:
	if (rawSession != NULL) {
		caps_destroySession(rawSession);
		rawSession = NULL;
	}

	if(image) {
		caps_destroyImage(image);
		image = NULL;
	}
#endif
}

}; // namespace android
