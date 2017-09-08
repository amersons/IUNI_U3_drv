/*************************************************************************************
 * 
 * Description:
 * 	Defines gionee feature APIs for camera HAL.
 *
 * Author : wutangzhi
 * Email  : wutz@gionee.com
 * Date   : 2012-06-11
 *
 *************************************************************************************/

#ifndef GN_CAMERA_FEATURE_BASE_H
#define GN_CAMERA_FEATURE_BASE_H

#include "IGNCameraFeature.h"

namespace android {         

class GNCameraFeatureBase : public IGNCameraFeature {

public:
	GNCameraFeatureBase();
	virtual int32 init();
	virtual void  deinit();
	virtual void  setCameraType(GNCameraType_t cameraType);
	virtual int32 setCameraListener(GNCameraFeatureListener* listener);
	virtual int32 setCapturePath(const char* filePath);
	virtual int32 initPreviewSize(int width, int height, GNImgFormat format);
	virtual int32 processPreview(void* inputBuffer, int size, int mask);
	virtual int32 processPicture(void* inputBuffer, int* size, int mask);
	virtual int32 processRaw(void* inputBuffer, int size, int width, int height, 
		GNImgFormat format, int mask);
	virtual int32 setEffect(GNLiveEffect_t effect);
	virtual int32 setPictureFrame(char* frameName);
	virtual int32 setHdr(GNHdr_t hdrMode);
	virtual int32 setLowlight(GNLowlight_t lowlightMode);
	virtual int32 setFaceBeauty(FaceBeautyParam const faceBeautyParam);
	virtual int32 setAgeGenderDetection(GNAgeGenderDetection_t const ageGenderDetection);
	virtual int32 setGestureShot(GNGestureShot_t gestureShotMode);
	virtual int32 setGestureDetection(GNGestureDetection_t gestureDetectionMode);
	virtual int32 setMirror(GNMirror_t mirrorMode);
	virtual int32 setSceneDetection(GNSceneDetection_t sceneDetectionMode);
	virtual int32 setNightShot(GNNightShot_t nightShotMode);
	virtual int32 setPicZoom(PicZoomParam const picZoomParam);
	virtual int32 startAUTORAMA(int32 num);
	virtual int32 stopAUTORAMA(int32 isMerge);
	virtual int32 setBurstCnt(GNCameraFeature_t cameraFeature, int count);
	virtual int32 getBurstCnt(GNCameraFeature_t cameraFeature);
	virtual int32 setOrientation(int orientation);
};
};

#endif /* GN_CAMERA_FEATURE_BASE_H */
