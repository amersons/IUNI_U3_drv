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
 
#ifndef ANDROID_ARCSOFT_CAMERA_FEATURE_H
#define ANDROID_ARCSOFT_CAMERA_FEATURE_H

#include "asvloffscreen.h"
#include "ammem.h"
#include "merror.h"

#include "ArcSoftNightShot.h"
#include "ArcSoftSceneDetection.h"
#include "ArcSoftFaceBeauty.h"
#include "ArcSoftGestureShot.h"
#include "ArcSoftLiveEffect.h"
#include "ArcSoftAgeGenderDetection.h"
#include "ArcSoftPicZoom.h"

#include <GNCameraFeatureBase.h>
#include <android/log.h>

#include <stdio.h>
#include <pthread.h>

namespace android { 
class ArcSoftCameraFeature : public GNCameraFeatureBase {
public:
    ArcSoftCameraFeature();
	~ArcSoftCameraFeature();
	
    static ArcSoftCameraFeature* createInstance();
    virtual void destroyInstance();
	
	virtual int32 init();
    virtual void  deinit();
    virtual int32 initPreviewSize(int width, int height, GNImgFormat format);
	virtual int32 setCameraListener(GNCameraFeatureListener* listener);
	virtual int32 setFaceBeauty(FaceBeautyParam const faceBeautyParam);
	virtual int32 setAgeGenderDetection(GNAgeGenderDetection_t const ageGenderDetection);
	virtual int32 setGestureShot(GNGestureShot_t gestureShotMode);
	virtual int32 setSceneDetection(GNSceneDetection_t sceneDetectionMode);
	virtual int32 setNightShot(GNNightShot_t nightShotMode);
	virtual int32 setEffect(GNLiveEffect_t effect);
	virtual int32 setOrientation(int orientation);
	virtual int32 setMirror(GNMirror_t mirrorMode);
	virtual int32 setPicZoom(PicZoomParam const picZoomParam);
	virtual int32 getBurstCnt(GNCameraFeature_t cameraFeature);
    virtual int32 processPreview(void* inputBuffer, int size, int mask);
    virtual int32 processRaw(void* inputBuffer, int size, int width, int height, GNImgFormat format, int mask);
	
private:
	int32 processFaceBeauty(LPASVLOFFSCREEN param, bool isPreview);
	int32 processAgeGenderDetection(LPASVLOFFSCREEN param, bool isPreview);
	int32 processGestureShot(LPASVLOFFSCREEN param);
	int32 processSceneDetection(LPASVLOFFSCREEN param);
	int32 processNightShot(LPASVLOFFSCREEN param);
	int32 processLiveEffect(LPASVLOFFSCREEN param, bool isMirror);
	int32 processPicZoom(LPASVLOFFSCREEN param);
	bool dumpImg(MUInt8 *addr, MUInt32 size, char const * const tag, char const * const filetype, int filenum);

private:
	int mGNCameraFeature;
	GNCameraFeatureListener* mListener;
	GNImgFormat mFormat;

    int mWidth;
    int mHeight;
	int mPreviewBufferSize;
	int mOrientation;

	bool mDumpImage;
	pthread_mutex_t mMutex;

	ASVLOFFSCREEN mPreviewData;

	ArcSoftFaceBeauty* mArcSoftFaceBeauty;
	ArcSoftGestureShot* mArcSoftGestureShot;
	ArcSoftNightShot* mArcSoftNightShot;
	ArcSoftSceneDetection* mArcSoftSceneDetection;
	ArcSoftLiveEffect* mArcSoftLiveEffect;
	ArcSoftAgeGenderDetection* mArcSoftAgeGenderDetection;
	ArcSoftPicZoom*	mArcSoftPicZoom;
};
};
#endif /* ANDROID_ARCSOFT_CAMERA_FEATURE_H */
