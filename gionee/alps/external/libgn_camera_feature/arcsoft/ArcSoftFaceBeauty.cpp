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

#define LOG_TAG "ArcSoftFaceBeauty"
#include <android/log.h>
#include <string.h>
 
#include "ArcSoftFaceBeauty.h"

namespace android { 

// Twelve groups of face beauty settings.
#define MAX_FB_LEVEL_SUPPORT 12
static BEAUTY_PARAM mFBParamArray[MAX_FB_LEVEL_SUPPORT] = 
{
	/************************************************************************************************
	  * {[1]Slender Face, [2]Skine Soften, [3]Eye Enlargment, [4]Skin Bright, [5]Eye Bright, [6]Arti Shine, [7]Teeth White}
	  ************************************************************************************************/
	{10, 10, 10, 0, 0, 0, 0},
	{15, 15, 15, 0, 0, 0, 0},
	{25, 25, 25, 0, 0, 0, 0},
	{30, 30, 30, 0, 0, 0, 0},
	{35, 35, 35, 0, 0, 0, 0},
	{40, 40, 40, 0, 0, 0, 0},
	{45, 45, 45, 0, 0, 0, 0},
	{55, 55, 55, 0, 0, 0, 0},
	{60, 60, 60, 0, 0, 0, 0},
	{65, 65, 65, 0, 0, 0, 0},
	{70, 70, 70, 0, 0, 0, 0},
	{75, 75, 75, 0, 0, 0, 0}
};


ArcSoftFaceBeauty::ArcSoftFaceBeauty()
	: mInitialized(false)
	, mParam()
	, mListener(NULL)
	, mFaceBeautyMode(GN_FACEBEAUTY_MODE_DEFAULT)
	, mArcSoftFaceProcess(NULL)
{

}

ArcSoftFaceBeauty::~ArcSoftFaceBeauty()
{
	
}

int32 
ArcSoftFaceBeauty::init()
{
	MRESULT res = 0; 

	if (mArcSoftFaceProcess == NULL) {
		mArcSoftFaceProcess = ArcSoftFaceProcess::getInstance();
	}
	
	return res;
}

void  
ArcSoftFaceBeauty::deinit()
{

}

int32
ArcSoftFaceBeauty::setFaceBeautyParam(FaceBeautyParam const faceBeautyParam)
{
	MRESULT res = 0;
	
	int mode = faceBeautyParam.faceBeautyMode;

	switch (mode) {
		case GN_FACEBEAUTY_MODE_DEFAULT:
			res = setFaceBeautyLevel(faceBeautyParam);
			break;
		case GN_FACEBEAUTY_MODE_AGEGENDER:
			res = setAgeGenderParam(faceBeautyParam);
			break;
		default:
			PRINTE("%s Unknown Beauty mode %d", __func__, mode);
			break;
	}

	mFaceBeautyMode = mode;

	return res;
}

int32 
ArcSoftFaceBeauty::processFaceBeauty(LPASVLOFFSCREEN param, bool isPreview)
{
	MRESULT res = 0;

	if (mArcSoftFaceProcess == NULL) {
		PRINTE("%s mArcSoftFaceProcess is NULL", __func__);
		return res;
	}
	
	if (!mArcSoftFaceProcess->isFaceProcessEnable()) {
		PRINTE("Haven't initialized the facebeauty enginer.");
		return res;
	}

	switch (mFaceBeautyMode) {
		case GN_FACEBEAUTY_MODE_DEFAULT:
			res = mArcSoftFaceProcess->processFaceBeauty(param, &mParam, isPreview);
			break;
			
		case GN_FACEBEAUTY_MODE_AGEGENDER:
			res = mArcSoftFaceProcess->processFaceBeautyEx(param, mAgeGenderParam, isPreview);
			break;
			
		default:
			PRINTE("%s Unknow beauty mode,process failed", __func__);
			break;
	}

	return res;
}

int32 
ArcSoftFaceBeauty::enableFaceBeauty(int width, int height)
{
	MRESULT res = 0; 

	if (mArcSoftFaceProcess != NULL) {
		mArcSoftFaceProcess->enableFaceProcess(width, height, GN_CAMERA_FACE_FEATURE_FACEBEAUTY);
	}

	return res;
}

int32 
ArcSoftFaceBeauty::disableFaceBeauty()
{
	MRESULT res = 0; 

	if (mArcSoftFaceProcess != NULL) {
		mArcSoftFaceProcess->disableFaceProcess(GN_CAMERA_FACE_FEATURE_FACEBEAUTY);
	}

	return res;
}

int32
ArcSoftFaceBeauty::setAgeGenderParam(FaceBeautyParam const faceBeautyParam)
{
	MRESULT rc = 0;

	for(int i = 0; i < faceBeautyParam.faceNum; i ++) {
		int feautyLevel = faceBeautyParam.ageGenderParam[i].feautyLevel;
		mAgeGenderParam.AgeGenderParam[i] = mFBParamArray[feautyLevel];
	}

	return rc;

}

int32
ArcSoftFaceBeauty::setFaceBeautyLevel(FaceBeautyParam const faceBeautyParam)
{
	MRESULT res = 0;

	FaceBeautyLevelParam_t param = faceBeautyParam.faceBeautyLevelParam;

	if (param.faceBeautyLevel > 0) {
		if (param.faceBeautyLevel > MAX_FB_LEVEL_SUPPORT) {
			PRINTE("Unsupport the level[%d]", param.faceBeautyLevel);
			return 0;
		}
	
		mParam = mFBParamArray[param.faceBeautyLevel - 1];
	
		PRINTD("%ld, %ld, %ld", mParam.lSlenderFaceLevel, mParam.lSkinSoftenLevel, mParam.lEyeEnlargmentLevel);
	} else {
		memset(&mParam, 0, sizeof(mParam));
		mParam.lSlenderFaceLevel	= param.slenderFaceLevel;
		mParam.lSkinSoftenLevel 	= param.skinSoftenLevel;
		mParam.lEyeEnlargmentLevel	= param.eyeEnlargmentLevel;
	}
	
	res = BS_SetParameter(&mParam);
	if (res != 0) {
		PRINTE("Failed to setParameter.");
	}

	return res;

}

};
