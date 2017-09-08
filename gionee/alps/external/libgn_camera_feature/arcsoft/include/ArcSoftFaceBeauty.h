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
 
#ifndef ANDROID_ARCSOFT_FACE_BEAUTY_H
#define ANDROID_ARCSOFT_FACE_BEAUTY_H

#include "arcsoft_beautyshot.h"
#include "asvloffscreen.h"
#include "ammem.h"
#include "merror.h"

#include "GNCameraFeatureDefs.h"
#include "GNCameraFeatureListener.h"

#include "ArcSoftFaceProcess.h"

namespace android { 
class ArcSoftFaceBeauty {
public:
    ArcSoftFaceBeauty();
	~ArcSoftFaceBeauty();
	
	int32 init();
    void  deinit();
	int32 setFaceBeautyParam(FaceBeautyParam const faceBeautyParam);
	int32 processFaceBeauty(LPASVLOFFSCREEN param, bool isPreview);
	int32 enableFaceBeauty(int width, int height);
	int32 disableFaceBeauty();

private:
	int32 setAgeGenderParam(FaceBeautyParam const faceBeautyParam);
	int32 setFaceBeautyLevel(FaceBeautyParam const faceBeautyParam);

private:
	BEAUTY_PARAM mParam;
	AFF_AGEGENDER_PARAM mAgeGenderParam;
	bool mInitialized;
	int mFaceBeautyMode;
	GNCameraFeatureListener* mListener;
	ArcSoftFaceProcess* mArcSoftFaceProcess;
};
};
#endif /* ANDROID_ARCSOFT_FACE_BEAUTY_H */
