/*************************************************************************************
 * 
 * Description:
 * 	Defines ArcSoft APIs for face process.
 *
 * Author : zhuangxiaojian
 * Email  : zhuangxj@gionee.com
 * Date   : 2014-10-28
 *
 *************************************************************************************/

#define LOG_TAG "ArcSoftFaceProcess"
#include <android/log.h>
#include <string.h>

#include "ArcSoftFaceProcess.h"

namespace android {
ArcSoftFaceProcess::ArcSoftFaceProcess()
	: mInitialized(false)
	, mGNFaceProcessFeature(GN_CAMERA_FACE_FEATURE_NONE)
{

}

ArcSoftFaceProcess::~ArcSoftFaceProcess()
{

}

ArcSoftFaceProcess*
ArcSoftFaceProcess::
getInstance()
{
#if 0

	if (mArcSoftFaceProcess == NULL) {
		mArcSoftFaceProcess = new ArcSoftFaceProcess();
	}

	return mArcSoftFaceProcess;
#else
	static ArcSoftFaceProcess instance;
	return &instance;
#endif
}

int32
ArcSoftFaceProcess::
init()
{
	MRESULT res = 0;

	return res;
}

void
ArcSoftFaceProcess::
deinit()
{
	if (mInitialized) {
		mInitialized = false;
		BS_Uninit();
	}
}

int32
ArcSoftFaceProcess::
enableFaceProcess(int width, int height, int featureMask)
{
	MRESULT res = 0;

	int mask = GN_CAMERA_FACE_FEATURE_FACEBEAUTY | GN_CAMERA_FACE_FEATURE_AGEGENDER_DETECTION;
	
	if ((featureMask & mask) == 0) {
		return res;
	}

	mGNFaceProcessFeature |= featureMask;

	if (!mInitialized) {
		mInitialized = true;

		res = BS_Init(width, height);
		if (res != 0) {
			PRINTE("Failed to initialized BS [%ld].", res);
		}
	}

	return res;
}

int32
ArcSoftFaceProcess::
disableFaceProcess(int featureMask)
{
	MRESULT res = 0;

	int mask = GN_CAMERA_FACE_FEATURE_FACEBEAUTY | GN_CAMERA_FACE_FEATURE_AGEGENDER_DETECTION;

	if ((featureMask & mask) == 0) {
		return res;
	}

	mGNFaceProcessFeature &= ~featureMask;
	
	if ((mGNFaceProcessFeature & mask) == 0) {
		if (mInitialized) {
			mInitialized = false;
			BS_Uninit();
		}
	}

	return res;
}

int32
ArcSoftFaceProcess::
processFaceBeauty(LPASVLOFFSCREEN imgSrc, BEAUTY_PARAM* param, bool isPreview)
{
	MRESULT res = 0;

	if (isPreview) {
		res = BS_ProcessPreview(imgSrc);
		if (res != 0) {
			PRINTE("Failed to call BS_ProcessPreview.");
		}
	} else {
		res = BS_ProcessImage(imgSrc, param);
		if (res != 0) {
			PRINTE("Failed to call BS_ProcessImage[#%ld].", res);
		}
	}

	return res;
}

int32
ArcSoftFaceProcess::
processFaceBeautyEx(LPASVLOFFSCREEN imgSrc, AFF_AGEGENDER_PARAM ageGenderparam, bool isPreview)
{
	MRESULT res = 0;

	if (isPreview) {
		res = BS_ProcessPreviewEx(imgSrc, ageGenderparam);
		if (res != 0) {
			PRINTE("Failed to call BS_ProcessPreviewEx[#%ld]", res);
		}
	} else {
		PRINTE("%s BS_ProcessImageEx", __func__);
		res = BS_ProcessImageEx(imgSrc, ageGenderparam);
		if (res != 0) {
			PRINTE("Failed to call BS_ProcessImageEx[#%ld]", res);
		}
	}

	return res;
}

int32
ArcSoftFaceProcess::
getAgeGenderResult(LPASVLOFFSCREEN param,AFF_AGEGENDERRESULT* result,bool isPreview)
{
	MRESULT res = 0;

	if (isPreview) {
		res = BS_GetPreviewAgeGenderResult(param, result);
	} else {
		res = BS_GetImageAgeGenderResult(param, result);
	}
	
	return res;
}

};
