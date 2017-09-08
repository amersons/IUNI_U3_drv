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

#define LOG_TAG "GNCameraFeatureBase"
#include <utils/Log.h>

#include <GNCameraFeatureBase.h>

namespace android {

GNCameraFeatureBase::
GNCameraFeatureBase()
{	
	//TODO
}

int32 
GNCameraFeatureBase::
init()
{
	int32 res = 0;
	
	return res;
}

void 
GNCameraFeatureBase::
deinit()
{

}

void
GNCameraFeatureBase::
setCameraType(GNCameraType_t cameraType) 
{
	
}

int32
GNCameraFeatureBase::
setCameraListener(GNCameraFeatureListener* listener) 
{
	int32 res = 0;

	return res;
}

int32
GNCameraFeatureBase::
setCapturePath(const char* filePath) 
{
	int32 res = 0;

	return res;
}


int32 
GNCameraFeatureBase::
setEffect(GNLiveEffect_t effect)
{
	int32 res = 0;

	return res;
}

int32 
GNCameraFeatureBase::
setPictureFrame(char* frameName)
{
	int32 res = 0;

	return res;
}

int32
GNCameraFeatureBase::
setHdr(GNHdr_t hdrMode)

{
	int32 res = 0;

	return res;

}

int32 
GNCameraFeatureBase::
setLowlight(GNLowlight_t lowlightMode)
{
	int32 res = 0;

	return res;
}

int32
GNCameraFeatureBase::
setFaceBeauty(FaceBeautyParam const faceBeautyParam)
{
	int32 res = 0;

	return res;
}

int32
GNCameraFeatureBase::setAgeGenderDetection(GNAgeGenderDetection_t const ageGenderDetection)
{
	int32 res = 0;

	return res;
}

int32
GNCameraFeatureBase::
setGestureShot(GNGestureShot_t gestureShotMode)
{
	int32 res = 0;

	return res;
}

int32
GNCameraFeatureBase::
setGestureDetection(GNGestureDetection_t gestureDetectionMode)
{
	int32 res = 0;

	return res;
}

int32
GNCameraFeatureBase::
setMirror(GNMirror_t mirrorMode)
{
	int32 res = 0;

	return res;
}

int32 
GNCameraFeatureBase::
setSceneDetection(GNSceneDetection_t sceneDetectionMode) 
{
	int32 res = 0;

	return res;
}

int32 
GNCameraFeatureBase::
setNightShot(GNNightShot_t nightShotMode)
{
	int32 res = 0;

	return res;
}

int32 
GNCameraFeatureBase::
setPicZoom(PicZoomParam const picZoomParam)
{
	int32 res = 0;

	return res;
}

int32 
GNCameraFeatureBase::
initPreviewSize(int width, int height, GNImgFormat format)
{
	int32 res = 0;

	return res;

}

int32 
GNCameraFeatureBase::
processPreview(void* inputBuffer, int size, int mask)
{
	int32 res = 0;

	return res;
}

int32 
GNCameraFeatureBase::
processPicture(void* inputBuffer, int* size, int mask)
{
	int32 res = 0;

	return res;
}

int32 
GNCameraFeatureBase::
processRaw(void* inputBuffer, int size, int width, int height, GNImgFormat format, int mask) 
{
	int32 res = 0;

	return res;
}

int32 
GNCameraFeatureBase::
startAUTORAMA(int32 num)
{
	int32 res = 0;

	return res;
}

int32 
GNCameraFeatureBase::
stopAUTORAMA(int32 isMerge)
{
	int32 res = 0;

	return res;
}

int32 
GNCameraFeatureBase::
setBurstCnt(GNCameraFeature_t cameraFeature, int count)
{
	int32 res = 0;

	return res;;
}

int32 
GNCameraFeatureBase::
getBurstCnt(GNCameraFeature_t cameraFeature)
{
	int32 res = 0;

	return res;;
}

int32 
GNCameraFeatureBase::
setOrientation(int orientation)
{
	int32 res = 0;

	return res;;
}

}; // namespace android
