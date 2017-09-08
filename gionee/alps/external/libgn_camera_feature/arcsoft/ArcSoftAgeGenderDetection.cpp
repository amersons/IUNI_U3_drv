/*************************************************************************************
 * 
 * Description:
 * 	Defines ArcSoft APIs for age gender detection.
 *
 * Author : zhuangxiaojian
 * Email  : zhuangxj@gionee.com
 * Date   : 2014-10-28
 *
 *************************************************************************************/

#define LOG_TAG "ArcSoftAgeGenderDetection"
#include <android/log.h>
#include <string.h>

#include "ArcSoftAgeGenderDetection.h"

namespace android {
ArcSoftAgeGenderDetection::ArcSoftAgeGenderDetection()
	: mInitialized(false)
	, mListener(NULL)
	, mArcSoftFaceProcess(NULL)
{
	mArcSoftFaceProcess = ArcSoftFaceProcess::getInstance();
}

ArcSoftAgeGenderDetection::~ArcSoftAgeGenderDetection()
{

}

int32
ArcSoftAgeGenderDetection::init()
{
	MRESULT res = 0;

	if (mArcSoftFaceProcess != NULL) {
		mArcSoftFaceProcess->init();
	}
	
	return res;
}

void
ArcSoftAgeGenderDetection::deinit()
{
	if (mArcSoftFaceProcess != NULL) {
		mArcSoftFaceProcess->deinit();
	}
}

int32
ArcSoftAgeGenderDetection::setCameraListener(GNCameraFeatureListener* listener)
{
	MRESULT res = 0;

	mListener = listener;

	return res;
}

int32
ArcSoftAgeGenderDetection::enableAgeGenderDetection(int width, int height)
{
	MRESULT res = 0;
	
	if (mArcSoftFaceProcess != NULL) {
		mArcSoftFaceProcess->enableFaceProcess(width, height, GN_CAMERA_FACE_FEATURE_AGEGENDER_DETECTION);
	}
	
	return res;
}

int32
ArcSoftAgeGenderDetection::disableAgeGenderDetection()
{
	MRESULT res = 0;
	
	if (mArcSoftFaceProcess != NULL) {
		mArcSoftFaceProcess->disableFaceProcess(GN_CAMERA_FACE_FEATURE_AGEGENDER_DETECTION);
	}
	
	return res;
}

int32
ArcSoftAgeGenderDetection::processAgeGenderDetection(LPASVLOFFSCREEN param, bool isPreview)
{
	MRESULT ret = 0;
	AFF_AGEGENDERRESULT ageGenderRes = {0};
	
	MMemSet(&ageGenderRes,0,sizeof(AFF_AGEGENDERRESULT));

	if (mArcSoftFaceProcess != NULL) {
		mArcSoftFaceProcess->getAgeGenderResult(param, &ageGenderRes, isPreview);
	}

	if (ageGenderRes.lFaceNumber > 0) {
		AgeGenderResult_t ageGenderResult = {0};
		memset(&ageGenderResult, 0, sizeof(AgeGenderResult_t));
		ageGenderResult.faceNumber = ageGenderRes.lFaceNumber;

		for (int i = 0; i < ageGenderRes.lFaceNumber; i ++) {
			ageGenderResult.ageResult[i]	= ageGenderRes.AgeResultArray[i];
			ageGenderResult.genderResult[i] = ageGenderRes.GenderResultArray[i];
			ageGenderResult.faceRect[i].top = ageGenderRes.FaceRect[i].top;
			ageGenderResult.faceRect[i].bottom = ageGenderRes.FaceRect[i].bottom;
			ageGenderResult.faceRect[i].left = ageGenderRes.FaceRect[i].left;
			ageGenderResult.faceRect[i].right = ageGenderRes.FaceRect[i].right;
			/*
			PRINTE("%s age %d gender %d, top %d bottom %d left %d right %d", __func__, 
				ageGenderResult.ageResult[i],
				ageGenderResult.genderResult[i],
				ageGenderResult.faceRect[i].top,
				ageGenderResult.faceRect[i].bottom,
				ageGenderResult.faceRect[i].left,
				ageGenderResult.faceRect[i].right);
			*/
		}
		
		if (mListener != NULL) {
			mListener->notify(GN_CAMERA_MSG_TYPE_AGEGENDER_DETECTION, 0, 0, 0, (void*)&ageGenderResult);
		}
	}

	return ret;
}


};
