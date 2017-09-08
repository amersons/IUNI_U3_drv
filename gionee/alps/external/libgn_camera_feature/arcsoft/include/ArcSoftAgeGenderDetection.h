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

#ifndef ANDROID_ARCSOFT_AGEGENDER_DETECTION_H
#define ANDROID_ARCSOFT_AGEGENDER_DETECTION_H

#include "arcsoft_beautyshot.h"
#include "asvloffscreen.h"
#include "ammem.h"
#include "merror.h"

#include "GNCameraFeatureListener.h"
#include "GNCameraFeatureDefs.h"

#include "ArcSoftFaceProcess.h"


namespace android {
class ArcSoftAgeGenderDetection {
public:
	ArcSoftAgeGenderDetection();
	~ArcSoftAgeGenderDetection();
	
	int32 init();
	void  deinit();
	int32 setCameraListener(GNCameraFeatureListener* listener);
	int32 processAgeGenderDetection(LPASVLOFFSCREEN param, bool isPreview);
	int32 enableAgeGenderDetection(int width, int height);
	int32 disableAgeGenderDetection();


private:	
	bool mInitialized;
	ArcSoftFaceProcess* mArcSoftFaceProcess;
	GNCameraFeatureListener* mListener;
};
};
#endif/*ANDROID_ARCSOFT_AGEGENDER_DETECTION_H*/

