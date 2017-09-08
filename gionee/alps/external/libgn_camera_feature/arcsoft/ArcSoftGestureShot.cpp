/*************************************************************************************
 * 
 * Description:
 * 	Defines ArcSoft APIs for face beauty.
 *
 * Author : wutangzhi
 * Email  : wutz@gionee.com
 * Date   : 2013-09-07
 *
 *************************************************************************************/

#define LOG_TAG "ArcSoftSceneDetection"
#include <android/log.h>
#include <string.h>
 
#include "ArcSoftGestureShot.h"

namespace android { 

ArcSoftGestureShot::ArcSoftGestureShot()
	: mInitialized(false)
	, mListener(NULL)
{

}

ArcSoftGestureShot::~ArcSoftGestureShot()
{
	
}

int32 
ArcSoftGestureShot::init()
{
	MRESULT res = 0; 

	return res;
}

void  
ArcSoftGestureShot::deinit()
{
	if (mInitialized) {
		mInitialized = false;
		VS_Uninit();
	}
}

int32 
ArcSoftGestureShot::setCameraListener(GNCameraFeatureListener* listener) 
{
	int res = 0;

	mListener = listener;
		
	return res;
}

int32 
ArcSoftGestureShot::processGestureShot(LPASVLOFFSCREEN param)
{
	MRESULT res = 0;
	MRECT rect = {0, 0, 0, 0};

	if (mListener == NULL || !mInitialized) {
		return res;
	}

	res = VS_ProcessPreview(param, &rect);
	if(res != 0) {
		PRINTE("Failed to call VS_ProcessPreview.");
	} else {
		if (rect.left != 0 || rect.right != 0 || rect.top != 0 || rect.bottom != 0) {
			mListener->notify(GN_CAMERA_SMG_TYPE_GESTURE_SHOT, 0, 0);
		}
	}

	return res;
}

int32 
ArcSoftGestureShot::enableGestureShot(int width, int height)
{
	MRESULT res = 0; 

	if (width == 0 && height == 0) {
		PRINTE("Invalid parameter.");
		return res;
	}

	if (!mInitialized) {
		mInitialized = true;

		res = VS_Init(width, height);
		if (res != 0) {
			PRINTE("Failed to initialized BS [%ld].", res);
		}
	}

	return res;
}

int32 
ArcSoftGestureShot::disableGestureShot()
{
	MRESULT res = 0; 

	if (mInitialized) {
		mInitialized = false;
		VS_Uninit();
	}

	return res;
}

};
