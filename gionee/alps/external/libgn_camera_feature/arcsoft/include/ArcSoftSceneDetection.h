/*************************************************************************************
 * 
 * Description:
 * 	Defines ArcSoft APIs for scene detection.
 *
 * Author : wutangzhi
 * Email  : wutz@gionee.com
 * Date   : 2013-09-07
 *
 *************************************************************************************/
 
#ifndef ANDROID_ARCSOFT_SCENE_DETECTION_H
#define ANDROID_ARCSOFT_SCENE_DETECTION_H

#include "Asd.h"
#include "merror.h"
#include "GNCameraFeatureDefs.h"
#include "GNCameraFeatureListener.h"


namespace android { 
class ArcSoftSceneDetection {
public:
    ArcSoftSceneDetection();
	~ArcSoftSceneDetection();
	
	int32 init();
    void  deinit();
	int32 setCameraListener(GNCameraFeatureListener* listener);
	int32 processSceneDetection(LPASVLOFFSCREEN param);
	int32 enableSceneDetection(int width, int height);
	int32 disableSceneDetection();

private:
	class SceneDetectionHandler : public ProcessCallback {
		public:
			SceneDetectionHandler(ArcSoftSceneDetection* thiz) 
			{
				mArcSoftSceneDetection = thiz;
			}

			int getSceneDetectionType(int type);
			virtual void onCallback(int result);
			
		private:
			ArcSoftSceneDetection* mArcSoftSceneDetection;
	};

private:
	Asd* mAsd;
	ASD_SCENETYPE mSceneType;

	pthread_mutex_t mMutex;
	bool mInitialized;

	GNCameraFeatureListener* mListener;
	SceneDetectionHandler* mSceneDetectionHandler;
	
};
};
#endif /* ANDROID_ARCSOFT_SCENE_DETECTION_H */
