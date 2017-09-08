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

#define LOG_TAG "CrunchfishCameraFeature"

#include "CrunchfishCameraFeature.h"

#include <cutils/properties.h>
#include <stdlib.h>
#include <cutils/log.h>
#include <time.h>
    
namespace android {

CrunchfishCameraFeature::CrunchfishCameraFeature() 
	: mGNCameraFeature(GN_CAMERA_FEATURE_NONE)
	, mOrientation(0)
	, mGestureDetectionMode(0)
	, mListener(NULL)
	,mGestureRotation(DO_NOT_ROTATE)
{
	mTouchlessA3D = new Engine();
	if (mTouchlessA3D == NULL) {
		PRINTE("Failed to create Crunchfish Engine.");
	}

	mGestureHandler = new GestureHandler(this);
	if (mGestureHandler == NULL) {
		PRINTE("Failed to create GestureHandler.");
	}

	pthread_mutex_init(&mMutex, NULL);
}

CrunchfishCameraFeature::
~CrunchfishCameraFeature() 
{
	if (mTouchlessA3D != NULL) {
		delete mTouchlessA3D;
		mTouchlessA3D = NULL;
	}

	if (mGestureHandler != NULL) {
		delete mGestureHandler;
		mGestureHandler = NULL;
	}

	pthread_mutex_destroy(&mMutex);  
}

CrunchfishCameraFeature*
CrunchfishCameraFeature::
createInstance() 
{
	return new CrunchfishCameraFeature();
}

void
CrunchfishCameraFeature::
destroyInstance() 
{
	delete this;
}

int32
CrunchfishCameraFeature::
init()
{
	int32 res = 0;

	return res;
}

void 
CrunchfishCameraFeature::
deinit()
{
	pthread_mutex_lock(&mMutex);

	unregisterGestureListener();
	
	mListener = NULL;

	pthread_mutex_unlock(&mMutex);
}

int32 
CrunchfishCameraFeature::
initPreviewSize(int width, int height, GNImgFormat format)
{
	int32 res = 0;

	pthread_mutex_lock(&mMutex);

	if (mTouchlessA3D != NULL) {
		res = mTouchlessA3D->init(width, height);
		if (res != TA3D_RESULT_OK) {
			PRINTE("Failed to initialized the Crunchfish Engine.");
		} 
	}

	pthread_mutex_unlock(&mMutex);

	return 0;
}

int32 
CrunchfishCameraFeature::
setCameraListener(GNCameraFeatureListener* listener)
{
	PRINTD("setCameraListener E");

	pthread_mutex_lock(&mMutex);
	
	mListener = listener;
	
	pthread_mutex_unlock(&mMutex);

	PRINTD("setCameraListener X");

	return 0;
}

int32 
CrunchfishCameraFeature::
setOrientation(int orientation) 
{
	pthread_mutex_lock(&mMutex);

	mOrientation = orientation;

	if (mOrientation == 0) {
		mGestureRotation = DO_NOT_ROTATE;
	} else {
		if (mOrientation == 90) {
			mGestureRotation = ROTATE_90;
		} else {
			if (mOrientation == 180) {
				mGestureRotation = ROTATE_180;
			} else {
				mGestureRotation = ROTATE_270;
			}
		}
	}

	pthread_mutex_unlock(&mMutex);

	return 0;
}

int32 
CrunchfishCameraFeature::
setGestureDetection(GNGestureDetection_t gestureDetectionMode) 
{
	int32 res = 0;
	
	PRINTD("gestureDetectionMode = %d", gestureDetectionMode); 

	pthread_mutex_lock(&mMutex);

	if (gestureDetectionMode == GN_GESTURE_DETECTION_NONE) {
		mGNCameraFeature &= ~GN_CAMERA_FEATURE_GESTURE_DETECTION;
		mGestureDetectionMode = 0;

		res = unregisterGestureListener();
 	} else if ((mGestureDetectionMode & (gestureDetectionMode << 1)) == 0){
		res = registerGestureListener(gestureDetectionMode);

		if (res == TA3D_RESULT_OK) {
			mGNCameraFeature |= GN_CAMERA_FEATURE_GESTURE_DETECTION;
			mGestureDetectionMode |= (gestureDetectionMode << 1);
		}
	}
	
	pthread_mutex_unlock(&mMutex);

	return 0;
}

int32 
CrunchfishCameraFeature::
registerGestureListener(GNGestureDetection_t gestureDetectionMode)
{
	int32 res = 0;
	GestureType type = 0;

	PRINTD("registerGestureListener E");

	switch (gestureDetectionMode) {
		case GN_GESTURE_DETECTION_OPEN_HAND_PRESENCE:
			type = OpenHandPresence::TYPE;
			break;
		case GN_GESTURE_DETECTION_FACE_PRESENCE:
			type = FacePresence::TYPE;
			break;
		case GN_GESTURE_DETECTION_FIST_PRESENCE:
			type = FistPresence::TYPE;
			break;
		default:
			type = -1;
			break;
	}

	PRINTD("registerGestureListener::type = %d", type);

	if (type != -1) {
		res = mTouchlessA3D->registerGestureListener(type, mGestureHandler);	
		if (res != TA3D_RESULT_OK) {
			PRINTE("Failed to register the Listener:[type = %d]", type);
		}
	}

	PRINTD("registerGestureListener X");

	return res;
}	

int32 
CrunchfishCameraFeature::
unregisterGestureListener()
{
	int32 res = 0;

	PRINTD("unregisterGestureListener E");

	if (mTouchlessA3D != NULL) {
		res = mTouchlessA3D->unregisterGestureListener(OpenHandPresence::TYPE, mGestureHandler);
		if (res != TA3D_RESULT_OK) {
			PRINTE("Failed to unregister the Listener:[type = %d]", OpenHandPresence::TYPE);
		}
		
		res = mTouchlessA3D->unregisterGestureListener(FacePresence::TYPE, mGestureHandler);
		if (res != TA3D_RESULT_OK) {
			PRINTE("Failed to unregister the Listener:[type = %d]", FacePresence::TYPE);
		}

		res = mTouchlessA3D->unregisterGestureListener(FistPresence::TYPE, mGestureHandler);
		if (res != TA3D_RESULT_OK) {
			PRINTE("Failed to unregister the Listener:[type = %d]", FistPresence::TYPE);
		}		
	}

	PRINTD("unregisterGestureListener X");

	return res;
}

int32 
CrunchfishCameraFeature::
processPreview(void* inputBuffer, int size, int mask)
{
	int32 res = 0;
	
	if (inputBuffer == NULL || size == 0) {
		PRINTE("the inputBuffer is null.");
		return -1;
	}

	pthread_mutex_lock(&mMutex);

	if ((mGNCameraFeature & 0XFFFF) == 0) {
		pthread_mutex_unlock(&mMutex); 
		return res;
	}

	if (mTouchlessA3D != NULL) {
		res = mTouchlessA3D->handleImage(currentTimeStamp(), (unsigned char*)inputBuffer,mGestureRotation); 
		if (res != TA3D_RESULT_OK) {
			PRINTE("Failed to handleFrame[#%d].", res);
		}
	}
	
	pthread_mutex_unlock(&mMutex); 

	return res;
}

unsigned long long
CrunchfishCameraFeature::
currentTimeStamp()
{
	struct timespec currentTime;
	unsigned long long timeStamp = 0;

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &currentTime);
	timeStamp = (currentTime.tv_sec * 1000 + currentTime.tv_nsec / 1000000);

	return timeStamp;
}


void
CrunchfishCameraFeature::
GestureHandler::
onGesture(const Gesture* pGesture)
{
	//pthread_mutex_lock(&mCrunchfishCameraFeature->mMutex);

	int32 ext1 = 0;
	int32 ext2 = 0;
	int32 ext3 = 0;
	int32 ext4 = 0;
	
	if (mCrunchfishCameraFeature->mListener == NULL) {
		PRINTE("Failed to callback gesture data as mListener is NULL.");
		return;
	}

	if (pGesture->getType() == OpenHandPresence::TYPE) {
		OpenHandPresence* pOpenHandlePresence = (OpenHandPresence*) pGesture;
		PRINTE("wutz : OpenHandPresence action = %d, x = %d, y = %d, z = %d, objectId = %d", pOpenHandlePresence->getAction(),
			pOpenHandlePresence->getCenterX(), pOpenHandlePresence->getCenterY(),
			pOpenHandlePresence->getZ(),pOpenHandlePresence->getObjectId());

		/*
		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		+ 	ext1: 	[type] 		[action] 
		+ 	ext2: 	[X data]
		+ 	ext3: 	[Y data]
		+ 	ext4: 	[Z data]
		+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		**/
		ext1 = ((0x000000FF & GN_GESTURE_DETECTION_OPEN_HAND_PRESENCE) << 24) 
			+ ((0x000000FF & pOpenHandlePresence->getAction()) << 16)
			+ (0x0000FFFF & pOpenHandlePresence->getObjectId()); 
		ext2 = pOpenHandlePresence->getCenterX();
		ext3 = pOpenHandlePresence->getCenterY();
		ext4 = pOpenHandlePresence->getZ();
		
		mCrunchfishCameraFeature->mListener->notify(GN_CAMERA_MSG_TYPE_GESTURE_DETECTION, ext1, ext2, ext3, ext4);
		
	} else if (pGesture->getType() == FacePresence::TYPE) {
		FacePresence* pFacePresence = (FacePresence*)pGesture;
		PRINTE("wutz : FacePresence action = %d, x = %d, y = %d, z = %d, objectId = %d", pFacePresence->getAction(),
			pFacePresence->getCenterX(), pFacePresence->getCenterY(),
			pFacePresence->getZ(),pFacePresence->getObjectId());

		ext1 = ((0x000000FF & GN_GESTURE_DETECTION_FACE_PRESENCE) << 24) 
			+ ((0x000000FF & pFacePresence->getAction()) << 16)
			+ (0x0000FFFF & pFacePresence->getObjectId()); 
		ext2 = pFacePresence->getCenterX();
		ext3 = pFacePresence->getCenterY();
		ext4 = pFacePresence->getZ();

		mCrunchfishCameraFeature->mListener->notify(GN_CAMERA_MSG_TYPE_GESTURE_DETECTION, ext1, ext2, ext3, ext4);
	} else if (pGesture->getType() == FistPresence::TYPE) {
		FistPresence* pFistPresence = (FistPresence*)pGesture;
		PRINTE("wutz : pFistPresence action = %d, x = %d, y = %d, z = %d, objectId = %d", pFistPresence->getAction(),
			pFistPresence->getCenterX(), pFistPresence->getCenterY(),
			pFistPresence->getZ(),pFistPresence->getObjectId());

		ext1 = ((0x000000FF & GN_GESTURE_DETECTION_FIST_PRESENCE) << 24) 
			+ ((0x000000FF & pFistPresence->getAction()) << 16)
			+ (0x0000FFFF & pFistPresence->getObjectId()); 
		ext2 = pFistPresence->getCenterX();
		ext3 = pFistPresence->getCenterY();
		ext4 = pFistPresence->getZ();

		mCrunchfishCameraFeature->mListener->notify(GN_CAMERA_MSG_TYPE_GESTURE_DETECTION, ext1, ext2, ext3, ext4);
	}

	//pthread_mutex_unlock(&mCrunchfishCameraFeature->mMutex);
}

bool 
CrunchfishCameraFeature::
dumpImg(unsigned char *addr, unsigned long size, char const * const tag, char const * const filetype, int filenum)
{
    
	char fileName[64] = {0};
    
    sprintf(fileName, "/sdcard/%s_%d.%s", tag, filenum, filetype);
	
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
