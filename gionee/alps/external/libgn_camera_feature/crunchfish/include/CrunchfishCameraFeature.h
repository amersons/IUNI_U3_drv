/*************************************************************************************
 * 
 * Description:
 * 	Defines Crunchfish APIs for camera HAL.
 *
 * Author : wutangzhi
 * Email  : wutz@gionee.com
 * Date   : 2013-05-08
 *
 *************************************************************************************/
 
#ifndef ANDROID_CRUNCHFISH_CAMERA_FEATURE_H
#define ANDROID_CRUNCHFISH_CAMERA_FEATURE_H

#include "touchless_a3d.h"
#include <pthread.h>
#include <GNCameraFeatureBase.h>
#include <stdio.h>

namespace android { 

using namespace TouchlessA3D;

class CrunchfishCameraFeature : public GNCameraFeatureBase {
public:
    CrunchfishCameraFeature();
	~CrunchfishCameraFeature();
	
    static CrunchfishCameraFeature* createInstance();
    virtual void destroyInstance();
	
	virtual int32 init();
    virtual void  deinit();
    virtual int32 initPreviewSize(int width, int height, GNImgFormat format);
	virtual int32 setCameraListener(GNCameraFeatureListener* listener);
	virtual int32 setOrientation(int orientation);
	virtual int32 setGestureDetection(GNGestureDetection_t gestureDetectionMode);
    virtual int32 processPreview(void* inputBuffer, int size, int mask);
private:
	unsigned long long currentTimeStamp();
	int32 registerGestureListener(GNGestureDetection_t gestureDetectionMode);
	int32 unregisterGestureListener();
	bool dumpImg(unsigned char *addr, unsigned long size, char const * const tag, char const * const filetype, int filenum);
	
	class GestureHandler : public GestureListener {
		public:
			GestureHandler(CrunchfishCameraFeature* thiz) 
			{
				mCrunchfishCameraFeature = thiz;
			}
			
			void onGesture(const Gesture* pGesture); 

		private:
			CrunchfishCameraFeature* mCrunchfishCameraFeature;
	};

private:
	int mGNCameraFeature;
	int mOrientation;
	Rotate mGestureRotation;
	int mGestureDetectionMode;
	GNCameraFeatureListener* mListener;

	GestureHandler* mGestureHandler;
	Engine* mTouchlessA3D;
	
	pthread_mutex_t mMutex;
};
};
#endif /* ANDROID_CRUNCHFISH_CAMERA_FEATURE_H */
