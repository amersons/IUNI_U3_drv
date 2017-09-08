/*************************************************************************************
 * 
 * Description:
 * 	Defines ArcSoft APIs for night shot.
 *
 * Author : wutangzhi
 * Email  : wutz@gionee.com
 * Date   : 2013-09-07
 *
 *************************************************************************************/
 
#ifndef ANDROID_ARCSOFT_NIGHT_SHOT_H
#define ANDROID_ARCSOFT_NIGHT_SHOT_H

#include "arcsoft_night_shot.h"
#include "asvloffscreen.h"
#include "ammem.h"
#include "merror.h"
#include "GNCameraFeatureDefs.h"


namespace android { 
class ArcSoftNightShot {
public:
    ArcSoftNightShot();
	
	int32 init();
    void  deinit();
	int32 getBurstCnt();
	int32 processNightShot(LPASVLOFFSCREEN param);
	int32 enableNightShot();
	int32 disableNightShot();

private:
	bool startEnhance(LPASVLOFFSCREEN param);
	int32 getMemSize(MUInt32 u32PixelArrayFormat, int width, int height);

private:

	MVoid* mMem;
	MHandle mMemMgr;
	MHandle mEnhancer;

	ANS_INPUTINFO mSrcInput;
	
	ASVLOFFSCREEN mSrcImages[MAX_INPUT_IMAGES];
	MLong mImageNum; 

	ASVLOFFSCREEN mDstImg;
	ANS_PARAM mParam;
};
};
#endif /* ANDROID_ARCSOFT_NIGHT_SHOT_H */
