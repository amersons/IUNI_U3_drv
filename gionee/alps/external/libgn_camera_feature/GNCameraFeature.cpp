/*************************************************************************************
 * 
 * Description:
 * 	Defines gionee feature APIs for camera hal.
 *
 * Author : wutangzhi
 * Email  : wutz@gionee.com
 * Date   : 2012-06-11
 *
 *************************************************************************************/
#define LOG_TAG "GNCameraFeature"

#include <cutils/log.h>
#include <android/log.h>

#include "GNCameraFeature.h"

#ifdef GN_SCALADO_FEATURE_SUPPORT
#include <ScaladoCameraFeature.h>
#endif

#ifdef GN_ARCSOFT_FEATURE_SUPPORT
#include <ArcSoftCameraFeature.h>
#endif

#ifdef GN_CRUNCHFISH_FEATURE_SUPPORT
#include <CrunchfishCameraFeature.h>
#endif

namespace android {

GNCameraFeature::
GNCameraFeature()
	: mScaladoCameraFeature(NULL)
	, mArcsoftCameraFeature(NULL)
	, mCrunchfishCameraFeature(NULL)
	, mGNCameraProfile(0)
	, mGNCameraFeatureMask(0)
{	

}

GNCameraFeature*
GNCameraFeature::
createInstance()
{
	return new GNCameraFeature();
}

void
GNCameraFeature::
destroyInstance()
{
	delete this;
}


int32
GNCameraFeature::
init()
{
	int32 res = 0;

#ifdef GN_SCALADO_FEATURE_SUPPORT
	if (mScaladoCameraFeature == NULL) {
		mScaladoCameraFeature = ScaladoCameraFeature::createInstance();
		mScaladoCameraFeature->init();
	}
#endif

#ifdef GN_ARCSOFT_FEATURE_SUPPORT
	if (mArcsoftCameraFeature == NULL) {
		mArcsoftCameraFeature = ArcSoftCameraFeature::createInstance();
		mArcsoftCameraFeature->init();
	}
#endif

#ifdef GN_CRUNCHFISH_FEATURE_SUPPORT
	if (mCrunchfishCameraFeature == NULL) {
		mCrunchfishCameraFeature = CrunchfishCameraFeature::createInstance();
		mCrunchfishCameraFeature->init();
	}
#endif

	return res;
}

void 
GNCameraFeature::
deinit()
{
	if (mScaladoCameraFeature != NULL) {
		mScaladoCameraFeature->deinit();
		mScaladoCameraFeature->destroyInstance();
		mScaladoCameraFeature = NULL;
	}

	if (mArcsoftCameraFeature != NULL) {
		mArcsoftCameraFeature->deinit();
		mArcsoftCameraFeature->destroyInstance();
		mArcsoftCameraFeature = NULL;
	}
	
    if (mCrunchfishCameraFeature != NULL) {
		mCrunchfishCameraFeature->deinit();
		mCrunchfishCameraFeature->destroyInstance();
		mCrunchfishCameraFeature = NULL;
	}

	mGNCameraFeatureMask = 0;
	mGNCameraProfile = 0;
}

void 
GNCameraFeature::
setCameraType(GNCameraType_t cameraType)
{
	if (mScaladoCameraFeature != NULL) {
		mScaladoCameraFeature->setCameraType(cameraType);
	}

	if (mArcsoftCameraFeature != NULL) {
		mArcsoftCameraFeature->setCameraType(cameraType);
	}
}

int32 
GNCameraFeature::
setCameraListener(GNCameraFeatureListener* listener) 
{
	int32 res = 0;

	if (mScaladoCameraFeature != NULL) {
		res = mScaladoCameraFeature->setCameraListener(listener);
	}

	if (mArcsoftCameraFeature != NULL) {
		res = mArcsoftCameraFeature->setCameraListener(listener);
	}
	
    if (mCrunchfishCameraFeature != NULL) {
		res = mCrunchfishCameraFeature->setCameraListener(listener);
	}
	
    return res;
}

int32 
GNCameraFeature::
setCapturePath(const char* filePath)
{
	int32 res = 0;
	
	if (mScaladoCameraFeature != NULL) {
		res = mScaladoCameraFeature->setCapturePath(filePath);
	}

	if (mArcsoftCameraFeature != NULL) {
		res = mArcsoftCameraFeature->setCapturePath(filePath);
	}

	return res;
}

int32 
GNCameraFeature::
setEffect(GNLiveEffect_t effect)
{
	int32 res = -1;
	int32 flag = 0;

#ifdef GN_SCALADO_LIVE_EFFECT_SUPPORT
	//Handle the Scalado live effect.
	if (mScaladoCameraFeature != NULL) {
		res = mScaladoCameraFeature->setEffect(effect);
	}

	if (res == 0) {
		if (effect == GN_LIVE_EFFECT_NONE) {
			mGNCameraProfile &= ~GN_CAMERA_PROFILE_SCALADO_EFFECT;
		} else {
			mGNCameraProfile |= GN_CAMERA_PROFILE_SCALADO_EFFECT;
		}
	}
#elif defined  GN_ARCSOFT_LIVE_EFFECT_SUPPORT
	//Handle the Arcsoft live effect.
	if (mArcsoftCameraFeature != NULL) {
		res = mArcsoftCameraFeature->setEffect(effect);
	}

	if (res == 0) {
		if (effect == GN_LIVE_EFFECT_NONE) {
			mGNCameraProfile &= ~GN_CAMERA_PROFILE_ARCSOFT_EFFECT;
		} else {
			mGNCameraProfile |= GN_CAMERA_PROFILE_ARCSOFT_EFFECT;
		}
	}
#endif

	flag = mGNCameraProfile & (GN_CAMERA_PROFILE_SCALADO_EFFECT | GN_CAMERA_PROFILE_ARCSOFT_EFFECT);
	updateFeatureMask(flag, GN_CAMERA_FEATURE_EFFECT);

	return res;
}

int32 
GNCameraFeature::
setPictureFrame(char* frameName)
{
	int32 res = -1;
	int32 flag = 0;

#ifdef GN_SCALADO_PICTURE_FRAME_SUPPORT
	if (mScaladoCameraFeature != NULL) {
		res = mScaladoCameraFeature->setPictureFrame(frameName);
	}

	if (res == 0) {
		if (frameName == NULL) {
			mGNCameraProfile &= ~GN_CAMERA_PROFILE_SCALADO_PICTURE_FRAME;
		} else {
			mGNCameraProfile |= GN_CAMERA_PROFILE_SCALADO_PICTURE_FRAME;
		}
	}
#endif

	flag = mGNCameraProfile & GN_CAMERA_PROFILE_SCALADO_PICTURE_FRAME;
	updateFeatureMask(flag, GN_CAMERA_FEATURE_PICTURE_FREAME);

	return res;
}

int32
GNCameraFeature::
setHdr(GNHdr_t hdrMode)

{
	int32 res = -1;
	int32 flag = 0;

#ifdef GN_SCALADO_HDR_SUPPORT
	if (mScaladoCameraFeature != NULL) {
		res = mScaladoCameraFeature->setHdr(hdrMode);
	}

	if (res == 0) {
		if (hdrMode == GN_HDR_OFF) {
			mGNCameraProfile &= ~GN_CAMERA_PROFILE_SCALADO_HDR;
		} else {
			mGNCameraProfile |= GN_CAMERA_PROFILE_SCALADO_HDR;
		}
	}
#endif

	
	flag = mGNCameraProfile & GN_CAMERA_PROFILE_SCALADO_HDR;
	updateFeatureMask(flag, GN_CAMERA_FEATURE_HDR);

	return res;
}

int32 
GNCameraFeature::
setLowlight(GNLowlight_t lowlightMode)
{
	int32 res = -1;
	int32 flag = 0;

#ifdef GN_SCALADO_LOWLIGHT_SUPPORT
	if (mScaladoCameraFeature != NULL) {
		res = mScaladoCameraFeature->setLowlight(lowlightMode);
	}

	if (res == 0) {
		if (lowlightMode == GN_LOWLIGHT_OFF) {
			mGNCameraProfile &= ~GN_CAMERA_PROFILE_SCALADO_LOWLIGHT;
		} else {
			mGNCameraProfile |= GN_CAMERA_PROFILE_SCALADO_LOWLIGHT;
		}
	}
#endif

	flag = mGNCameraProfile & GN_CAMERA_PROFILE_SCALADO_LOWLIGHT;
	updateFeatureMask(flag, GN_CAMERA_FEATURE_LOWLIGHT);

	return res;;
}

int32 
GNCameraFeature::
setGestureShot(GNGestureShot_t gestureShotMode)
{
	int32 res = -1;
	int32 flag = 0;

#ifdef GN_ARCSOFT_GESTURE_SHOT_SUPPORT
	if (mArcsoftCameraFeature != NULL) {
		res = mArcsoftCameraFeature->setGestureShot(gestureShotMode);
	}

	if (res == 0) {
		if (gestureShotMode == GN_GESTURE_SHOT_OFF) {
			mGNCameraProfile &= ~GN_CAMERA_PROFILE_ARCSOFT_GESTURE_SHOT;
		} else {
			mGNCameraProfile |= GN_CAMERA_PROFILE_ARCSOFT_GESTURE_SHOT;
		}
	}
#endif

	flag = mGNCameraProfile & GN_CAMERA_PROFILE_ARCSOFT_GESTURE_SHOT;
	updateFeatureMask(flag, GN_CAMERA_FEATURE_GESTURE_SHOT);

	return res;;
}

int32 
GNCameraFeature::
setGestureDetection(GNGestureDetection_t gestureDetectionMode)
{
	int32 res = -1;
	int32 flag = 0;

#ifdef GN_CRUNCHFISH_GESTURE_DETECTION_SUPPORT
	if (mCrunchfishCameraFeature != NULL) {
		res = mCrunchfishCameraFeature->setGestureDetection(gestureDetectionMode);
	}

	if (res == 0) {
		if (gestureDetectionMode == GN_GESTURE_DETECTION_NONE) {
			mGNCameraProfile &= ~GN_CAMERA_PROFILE_CRUNCHFISH_GESTURE_DETECTION;
		} else {
			mGNCameraProfile |= GN_CAMERA_PROFILE_CRUNCHFISH_GESTURE_DETECTION;
		}
	}
#endif

	flag = mGNCameraProfile & GN_CAMERA_PROFILE_CRUNCHFISH_GESTURE_DETECTION;
	updateFeatureMask(flag, GN_CAMERA_FEATURE_GESTURE_DETECTION);

	return res;;
}


int32 
GNCameraFeature::
setFaceBeauty(FaceBeautyParam const faceBeautyParam)
{
	int32 res = -1;
	int32 flag = 0;

#ifdef GN_ARCSOFT_FACE_BEAUTY_SUPPORT
	if (mArcsoftCameraFeature != NULL) {
		res = mArcsoftCameraFeature->setFaceBeauty(faceBeautyParam);
	} 

	if (res == 0) {
		if (faceBeautyParam.faceBeautyState == GN_FACEBEAUTY_OFF) {
			mGNCameraProfile &= ~GN_CAMERA_PROFILE_ARCSOFT_FACE_BEAUTY;
		} else {
			mGNCameraProfile |= GN_CAMERA_PROFILE_ARCSOFT_FACE_BEAUTY;
		}
	}
#endif

	flag = mGNCameraProfile & GN_CAMERA_PROFILE_ARCSOFT_FACE_BEAUTY;
	updateFeatureMask(flag, GN_CAMERA_FEATURE_FACE_BEAUTY);

	return res;;
}

int32 
GNCameraFeature::
setAgeGenderDetection(GNAgeGenderDetection_t const ageGenderDetection)
{
	int32 res = -1;
	int32 flag = 0;

#ifdef GN_ARCSOFT_AGEGENDER_DETECTION_SUPPORT
	if (mArcsoftCameraFeature != NULL) {
		res = mArcsoftCameraFeature->setAgeGenderDetection(ageGenderDetection);
	} 

	if (res == 0) {
		if (ageGenderDetection == GN_AGEGENDER_DETECTION_OFF) {
			mGNCameraProfile &= ~GN_CAMERA_PROFILE_AGEGENDER_DETECTION;
		} else {
			mGNCameraProfile |= GN_CAMERA_PROFILE_AGEGENDER_DETECTION;
		}
	}
#endif

	flag = mGNCameraProfile & GN_CAMERA_PROFILE_AGEGENDER_DETECTION;
	updateFeatureMask(flag, GN_CAMERA_FEATUER_AGEGENDER_DETECTION);
	
	return res;
}

int32 
GNCameraFeature::
setMirror(GNMirror_t mirrorMode)
{
	int32 res = -1;
	int32 flag = 0;
	
#ifdef GN_SCALADO_MIRROR_SUPPORT
	if (mScaladoCameraFeature != NULL) {
		res = mScaladoCameraFeature->setMirror(mirrorMode);
	}

	if (res == 0) {
		if (mirrorMode == GN_MIRROR_OFF) {
			mGNCameraProfile &= ~GN_CAMERA_PROFILE_SCALADO_MIRROR;
		} else {
			mGNCameraProfile |= GN_CAMERA_PROFILE_SCALADO_MIRROR;
		}
	}
#endif

#ifdef GN_ARCSOFT_LIVE_EFFECT_SUPPORT
	if (mGNCameraProfile & GN_CAMERA_PROFILE_SCALADO_MIRROR) {
		if (mArcsoftCameraFeature != NULL) {
			res = mArcsoftCameraFeature->setMirror(mirrorMode);
		}
	}
#endif

	flag = mGNCameraProfile & GN_CAMERA_PROFILE_SCALADO_MIRROR;
	updateFeatureMask(flag, GN_CAMERA_FEATUER_MIRROR);

	return res;
}

int32 
GNCameraFeature::
setSceneDetection(GNSceneDetection_t sceneDetectionMode)
{
	int32 res = -1;
	int32 flag = 0;
	
#ifdef GN_ARCSOFT_SCENE_DETECTION_SUPPORT
	if (mArcsoftCameraFeature != NULL) {
		res = mArcsoftCameraFeature->setSceneDetection(sceneDetectionMode);
	}

	if (res == 0) {
		if (sceneDetectionMode == GN_SCENE_DETECTION_OFF) {
			mGNCameraProfile &= ~GN_CAMERA_PROFILE_ARCSOFT_SCENE_DETECTION;
		} else {
			mGNCameraProfile |= GN_CAMERA_PROFILE_ARCSOFT_SCENE_DETECTION;
		}
	}
#endif

	flag = mGNCameraProfile & GN_CAMERA_PROFILE_ARCSOFT_SCENE_DETECTION;
	updateFeatureMask(flag, GN_CAMERA_FEATUER_SCENE_DETECTION);

	return res;
}

int32 
GNCameraFeature::
setNightShot(GNNightShot_t nightShotMode)
{
	int32 res = -1;
	int32 flag = 0;
	
#ifdef GN_ARCSOFT_NIGHT_SHOT_SUPPORT
	if (mArcsoftCameraFeature != NULL) {
		res = mArcsoftCameraFeature->setNightShot(nightShotMode);
	}

	if (res == 0) {
		if (nightShotMode == GN_NIGHT_SHOT_OFF) {
			mGNCameraProfile &= ~GN_CAMERA_PROFILE_ARCSOFT_NIGHT_SHOT;
		} else {
			mGNCameraProfile |= GN_CAMERA_PROFILE_ARCSOFT_NIGHT_SHOT;
		}
	}
#endif

	flag = mGNCameraProfile & GN_CAMERA_PROFILE_ARCSOFT_NIGHT_SHOT;
	updateFeatureMask(flag, GN_CAMERA_FEATUER_NIGHT_SHOT);

	return res;
}

int32
GNCameraFeature::
setPicZoom(PicZoomParam const picZoomParam)
{
	int32 res = -1;
	int32 flag = 0;

#ifdef GN_ARCSOFT_PIC_ZOOM_SUPPORT
	if (mArcsoftCameraFeature != NULL) {
		res = mArcsoftCameraFeature->setPicZoom(picZoomParam);
	}

	if (res == 0) {
		if (picZoomParam.picZoomMode == GN_PIC_ZOOM_OFF) {
			mGNCameraProfile &= ~GN_CAMERA_PROFILE_ARCSOFT_PIC_ZOOM;
		} else {
			mGNCameraProfile |= GN_CAMERA_PROFILE_ARCSOFT_PIC_ZOOM;
		}
	}
#endif

	flag = mGNCameraProfile & GN_CAMERA_PROFILE_ARCSOFT_PIC_ZOOM;
	updateFeatureMask(flag, GN_CAMERA_PROFILE_ARCSOFT_PIC_ZOOM);

	return res;
}

int32 
GNCameraFeature::
initPreviewSize(int width, int height, GNImgFormat format)
{
	int32 res = 0;
	
	if (mArcsoftCameraFeature != NULL) {
		res = mArcsoftCameraFeature->initPreviewSize(width, height, format);
	}

	if (mScaladoCameraFeature != NULL) {
		res = mScaladoCameraFeature->initPreviewSize(width, height, format);
	}

	if (mCrunchfishCameraFeature != NULL) {
		res = mCrunchfishCameraFeature->initPreviewSize(width, height, format);
	}

	return res;
}

int32 
GNCameraFeature::
processPreview(void* inputBuffer, int size, int mask)
{
	int32 res = 0;
	int profileMask = 0;

	if ((mask & mGNCameraFeatureMask) == 0) {
		return res;
	}
	
	profileMask = getProfileMask(mask);
	if (profileMask == 0) {
		return res;
	}

	if (profileMask & (GN_CAMERA_PROFILE_ARCSOFT_FACE_BEAUTY | GN_CAMERA_PROFILE_ARCSOFT_GESTURE_SHOT 
		| GN_CAMERA_PROFILE_ARCSOFT_SCENE_DETECTION | GN_CAMERA_PROFILE_AGEGENDER_DETECTION)) {
		if (mArcsoftCameraFeature != NULL) {
			res = mArcsoftCameraFeature->processPreview(inputBuffer, size, mask);
		}
	}

	if (profileMask & (GN_CAMERA_PROFILE_SCALADO_EFFECT | GN_CAMERA_PROFILE_SCALADO_PANORAMA 
		| GN_CAMERA_PROFILE_SCALADO_MIRROR)) {
		if (mScaladoCameraFeature != NULL) {
			res = mScaladoCameraFeature->processPreview(inputBuffer, size, mask);
		}
	}

    if (profileMask & GN_CAMERA_PROFILE_CRUNCHFISH_GESTURE_DETECTION) {
        if (mCrunchfishCameraFeature != NULL) {
            res = mCrunchfishCameraFeature->processPreview(inputBuffer, size, mask);
        }
    }
	
    return res;
}

int32 
GNCameraFeature::
processPicture(void* inputBuffer, int* size, int mask)
{
	int32 res = 0;
	int profileMask = 0;

	if ((mask & mGNCameraFeatureMask) == 0) {
		return res;
	}

	profileMask = getProfileMask(mask);
	if (profileMask == 0) {
		return res;
	}

	if (profileMask & (GN_CAMERA_PROFILE_SCALADO_EFFECT | GN_CAMERA_PROFILE_SCALADO_HDR 
		| GN_CAMERA_PROFILE_SCALADO_LOWLIGHT | GN_CAMERA_PROFILE_SCALADO_PANORAMA 
		| GN_CAMERA_PROFILE_SCALADO_PICTURE_FRAME | GN_CAMERA_PROFILE_SCALADO_MIRROR)) {
		if (mScaladoCameraFeature != NULL) {
			res = mScaladoCameraFeature->processPicture(inputBuffer, size, mask);
		}
	}

	return res;
}

int32 
GNCameraFeature::
processRaw(void* inputBuffer, int size, int width, int height, GNImgFormat format, int mask) 
{
	int32 res = 0;
	int profileMask = 0;

	if ((mask & mGNCameraFeatureMask) == 0) {
		return res;
	}

	profileMask = getProfileMask(mask);
	if (profileMask == 0) {
		return res;
	}

	if (profileMask & (GN_CAMERA_PROFILE_ARCSOFT_FACE_BEAUTY | GN_CAMERA_PROFILE_ARCSOFT_GESTURE_SHOT
		| GN_CAMERA_PROFILE_ARCSOFT_NIGHT_SHOT | GN_CAMERA_PROFILE_ARCSOFT_EFFECT
		| GN_CAMERA_PROFILE_AGEGENDER_DETECTION | GN_CAMERA_PROFILE_ARCSOFT_PIC_ZOOM)) {
		if (mArcsoftCameraFeature != NULL) {
			res = mArcsoftCameraFeature->processRaw(inputBuffer, size, width, height, format, mask);
		}
	} 

	if (profileMask & (GN_CAMERA_PROFILE_SCALADO_EFFECT | GN_CAMERA_PROFILE_SCALADO_HDR 
		| GN_CAMERA_PROFILE_SCALADO_LOWLIGHT | GN_CAMERA_PROFILE_SCALADO_PANORAMA 
		| GN_CAMERA_PROFILE_SCALADO_PICTURE_FRAME | GN_CAMERA_PROFILE_SCALADO_MIRROR)) {
		if (mScaladoCameraFeature != NULL) {
			res = mScaladoCameraFeature->processRaw(inputBuffer, size, width, height, format, mask);
		}
	}

	return res;
}

int32 
GNCameraFeature::
startAUTORAMA(int32 num)
{
	int32 res = -1;
	if (mGNCameraProfile != 0) {
		return res;
	}

#ifdef GN_SCALADO_AUTORAMA_SUPPORT
	if (mScaladoCameraFeature != NULL) {
		res = mScaladoCameraFeature->startAUTORAMA(num);
	}

	if (res == 0) {
		mGNCameraProfile |= GN_CAMERA_PROFILE_SCALADO_PANORAMA;
	}
#endif

	return res;
}

int32 
GNCameraFeature::
stopAUTORAMA(int32 isMerge)
{
	int32 res = -1;

#ifdef GN_SCALADO_AUTORAMA_SUPPORT
	if (mScaladoCameraFeature != NULL) {
		res = mScaladoCameraFeature->stopAUTORAMA(isMerge);
	}

	if (res == 0) {
		mGNCameraProfile &= ~GN_CAMERA_PROFILE_SCALADO_PANORAMA;
	}
#endif

	return res;
}

int32 
GNCameraFeature::
setBurstCnt(GNCameraFeature_t cameraFeature, int count)
{
	int32 res = -1;

	if (mScaladoCameraFeature != NULL) {
		res = mScaladoCameraFeature->setBurstCnt(cameraFeature, count);
	}

	return res;;
}

int32 
GNCameraFeature::
getBurstCnt(GNCameraFeature_t cameraFeature)
{
	int32 res = 0;

	if (mArcsoftCameraFeature != NULL) {
		if (mGNCameraProfile & (GN_CAMERA_PROFILE_ARCSOFT_NIGHT_SHOT | GN_CAMERA_PROFILE_ARCSOFT_PIC_ZOOM)) {
			res = mArcsoftCameraFeature->getBurstCnt(cameraFeature);
		}
	}

	return res;;
}

int32 
GNCameraFeature::
setOrientation(int orientation)
{
	int32 res = 0;

	if (mScaladoCameraFeature != NULL) {
		res = mScaladoCameraFeature->setOrientation(orientation);
	}

	if (mArcsoftCameraFeature != NULL) {
		res = mArcsoftCameraFeature->setOrientation(orientation);
	}

	if (mCrunchfishCameraFeature != NULL) {
		res = mCrunchfishCameraFeature->setOrientation(orientation);
	}
	
    return res;;
}

void
GNCameraFeature::
updateFeatureMask(int32 flag, int32 mask)
{
	if (flag != 0) {
		mGNCameraFeatureMask |= mask;
	} else {
		mGNCameraFeatureMask &= ~mask;
	}
}

int32
GNCameraFeature::
getProfileMask(int32 featureMask)
{
	int32 profileMask = 0;

	featureMask &= mGNCameraFeatureMask;

	if (featureMask & GN_CAMERA_FEATURE_HDR) {
		profileMask = (GN_CAMERA_PROFILE_SCALADO_HDR & mGNCameraProfile);
	}

	if (featureMask & GN_CAMERA_FEATURE_LOWLIGHT) {
		profileMask |= (GN_CAMERA_PROFILE_SCALADO_LOWLIGHT & mGNCameraProfile);
	}

	if (featureMask & GN_CAMERA_FEATURE_EFFECT) {
		profileMask |= ((GN_CAMERA_PROFILE_SCALADO_EFFECT | GN_CAMERA_PROFILE_ARCSOFT_EFFECT) & mGNCameraProfile);
	}

	if (featureMask & GN_CAMERA_FEATURE_PICTURE_FREAME) {
		profileMask |= (GN_CAMERA_PROFILE_SCALADO_PICTURE_FRAME & mGNCameraProfile);
	}

	if (featureMask & GN_CAMERA_FEATURE_PANORAMA) {
		profileMask |= (GN_CAMERA_PROFILE_SCALADO_PANORAMA & mGNCameraProfile);
	}

	if (featureMask & GN_CAMERA_FEATURE_FACE_BEAUTY) {
		profileMask |= (GN_CAMERA_PROFILE_ARCSOFT_FACE_BEAUTY & mGNCameraProfile);
	}

	if (featureMask & GN_CAMERA_FEATURE_GESTURE_SHOT) {
		profileMask |= (GN_CAMERA_PROFILE_ARCSOFT_GESTURE_SHOT & mGNCameraProfile);
	}

	if (featureMask & GN_CAMERA_FEATURE_GESTURE_DETECTION) {
		profileMask |= (GN_CAMERA_PROFILE_CRUNCHFISH_GESTURE_DETECTION & mGNCameraProfile);
	}

	if (featureMask & GN_CAMERA_FEATUER_MIRROR) {
		profileMask |= (GN_CAMERA_PROFILE_SCALADO_MIRROR & mGNCameraProfile);
	}

	if (featureMask & GN_CAMERA_FEATUER_SCENE_DETECTION) {
		profileMask |= (GN_CAMERA_PROFILE_ARCSOFT_SCENE_DETECTION & mGNCameraProfile);
	}

	if (featureMask & GN_CAMERA_FEATUER_NIGHT_SHOT) {
		profileMask |= (GN_CAMERA_PROFILE_ARCSOFT_NIGHT_SHOT & mGNCameraProfile);
	}

	if (featureMask & GN_CAMERA_FEATUER_AGEGENDER_DETECTION) {
		profileMask |= (GN_CAMERA_PROFILE_AGEGENDER_DETECTION & mGNCameraProfile);
	}

	if (featureMask & GN_CAMERA_FEATURE_PIC_ZOOM) {
		profileMask |= (GN_CAMERA_PROFILE_ARCSOFT_PIC_ZOOM & mGNCameraProfile);
	}

	return profileMask;
}

}; // namespace android
