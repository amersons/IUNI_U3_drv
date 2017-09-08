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

#ifndef ANDROID_ARCSOFT_FACE_PROCESS_H
#define ANDROID_ARCSOFT_FACE_PROCESS_H

#include "arcsoft_beautyshot.h"
#include "asvloffscreen.h"
#include "ammem.h"
#include "merror.h"

#include "GNCameraFeatureListener.h"
#include "GNCameraFeatureDefs.h"

namespace android {
class ArcSoftFaceProcess {
private:
	ArcSoftFaceProcess();
	~ArcSoftFaceProcess();
	

public:
	int32 init();
	void  deinit();
	int32 enableFaceProcess(int width, int height, int featureMask);
	int32 disableFaceProcess(int featureMask);
	int32 getAgeGenderResult(LPASVLOFFSCREEN param, AFF_AGEGENDERRESULT* result, bool isPreview);
	int32 processFaceBeauty(LPASVLOFFSCREEN imgSrc, BEAUTY_PARAM* param, bool isPreview);
	int32 processFaceBeautyEx(LPASVLOFFSCREEN imgSrc, AFF_AGEGENDER_PARAM ageGenderparam, bool isPreview);
	bool  isFaceProcessEnable() {return mInitialized;};

public:
	static ArcSoftFaceProcess* getInstance();

private:	
	static ArcSoftFaceProcess* mArcSoftFaceProcess;
	bool mInitialized;
	int mGNFaceProcessFeature;
};
};
#endif/*ANDROID_ARCSOFT_FACE_PROCESS_H*/

