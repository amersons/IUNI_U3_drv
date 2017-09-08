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

#define LOG_TAG "ArcSoftSceneDetection"
#include <android/log.h>
#include <string.h>
 
#include "ArcSoftSceneDetection.h"

namespace android { 

#define SCENE_TYPE_SIZE	9

static ASD_SCENETYPE mAsdSceneTypes[] = {
									ASD_AUTO, 
									ASD_PORTRAIT, 
									ASD_BACKLIT, 
									ASD_PORTRAIT_NIGHT, 
									ASD_PORTRAIT_BACKLIT, 
									ASD_NIGHT, 
									ASD_GOURMET,
									ASD_TEXT,
									ASD_SPORT
									};
static GNCameraSceneDetectionType_t mGnCameraSceneTypes[] = {
									GN_CAMERA_SCENE_DETECTION_TYPE_AUTO,
									GN_CAMERA_SCENE_DETECTION_TYPE_PORTRAIT,
									GN_CAMERA_SCENE_DETECTION_TYPE_BACKLIT,
									GN_CAMERA_SCENE_DETECTION_TYPE_PORTRAIT_NIGHT,
									GN_CAMERA_SCENE_DETECTION_TYPE_PORTRAIT_BACKLIT,
									GN_CAMERA_SCENE_DETECTION_TYPE_NIGHT,
									GN_CAMERA_SCENE_DETECTION_TYPE_GOURMET,
									GN_CAMERA_SCENE_DETECTION_TYPE_TEXT,
									GN_CAMERA_SCENE_DETECTION_TYPE_SPORT
									};

ArcSoftSceneDetection::ArcSoftSceneDetection()
	: mSceneType(ASD_AUTO)
	, mListener(NULL)
	, mSceneDetectionHandler(NULL)
	, mAsd(NULL)
	, mInitialized(false)
{
	mSceneDetectionHandler = new SceneDetectionHandler(this);
	if (mSceneDetectionHandler == NULL) {
		PRINTE("Failed to new SceneDetectionHandler.");
	}

	mAsd = new Asd();
	if (mAsd == NULL) {
		PRINTE("Failed to new Asd.");
	}

	pthread_mutex_init(&mMutex, NULL);
}

ArcSoftSceneDetection::~ArcSoftSceneDetection()
{
	if (mSceneDetectionHandler != NULL) {
		delete mSceneDetectionHandler;
		mSceneDetectionHandler = NULL;
	}

	if (mAsd != NULL) {
		delete mAsd;
		mAsd = NULL;
	}

	pthread_mutex_destroy(&mMutex);
}

int32 
ArcSoftSceneDetection::init()
{
	MRESULT res = 0; 

	return res;
}

void  
ArcSoftSceneDetection::deinit()
{
	if (mAsd != NULL && mInitialized) {
		mAsd->setProcessCallback(NULL);
		mAsd->uninit();
		mInitialized = false;
	}
}

int32 
ArcSoftSceneDetection::setCameraListener(GNCameraFeatureListener* listener)
{
	MRESULT res = 0; 

	pthread_mutex_lock(&mMutex);
	mListener = listener;
	pthread_mutex_unlock(&mMutex);

	return res;
}

int32 
ArcSoftSceneDetection::processSceneDetection(LPASVLOFFSCREEN param)
{
	MRESULT res = 0;

	if (mListener == NULL || !mInitialized) {
		return res;
	}
	
	if (mAsd != NULL) {
		res = mAsd->process(param ,0);
		if (res != 0) {
			PRINTD("Failed to process scene detection.");
		}
	}

	return res;
}

int32 
ArcSoftSceneDetection::enableSceneDetection(int width, int height)
{
	MRESULT res = 0; 

	if (width == 0 && height == 0) {
		PRINTE("Invalid parameter.");
		return res;
	}

	if (mAsd != NULL && !mInitialized) {
		res = mAsd->init(width, height);
		if (res != NULL) {
			PRINTE("Failed to initialize the scene detection enginer.");
		} else {
			mInitialized = true;
			mAsd->setModeProfile(ASD_PORTRAIT|ASD_PORTRAIT_NIGHT|ASD_PORTRAIT_BACKLIT|ASD_NIGHT|ASD_BACKLIT|ASD_GOURMET|ASD_TEXT);
			mAsd->setProcessCallback(mSceneDetectionHandler);
		}
	}

	return res;
}

int32 
ArcSoftSceneDetection::disableSceneDetection()
{
	MRESULT res = 0; 
	
	if (mAsd != NULL && mInitialized) {
		mAsd->setProcessCallback(NULL);
		mAsd->uninit();
		mInitialized = false;
	}

	return res;
}

void
ArcSoftSceneDetection::
SceneDetectionHandler::
onCallback(int result) 
{
	pthread_mutex_lock(&mArcSoftSceneDetection->mMutex);

	if (mArcSoftSceneDetection != NULL && mArcSoftSceneDetection->mListener != NULL) {
		mArcSoftSceneDetection->mListener->notify(GN_CAMERA_MSG_TYPE_SCENE_DETECTION, getSceneDetectionType(result), 0);
	}

	pthread_mutex_unlock(&mArcSoftSceneDetection->mMutex);
}

int
ArcSoftSceneDetection::
SceneDetectionHandler::
getSceneDetectionType(int type)
{
	int res = 0;
	int i = 0;

	for (i = 0; i < SCENE_TYPE_SIZE; i ++) {
		if (type == (int)mAsdSceneTypes[i]) {
			break;
		}
	}

	if (i < SCENE_TYPE_SIZE) {
		res = (int) mGnCameraSceneTypes[i];
	}

	return res;
}

};
