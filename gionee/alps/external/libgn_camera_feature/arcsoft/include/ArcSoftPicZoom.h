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
 
#ifndef ANDROID_ARCSOFT_PIC_ZOOM_H
#define ANDROID_ARCSOFT_PIC_ZOOM_H

#include "arcsoft_piczoom.h"
#include "ammem.h"

#include "GNCameraFeatureDefs.h"


namespace android { 
class ArcSoftPicZoom {
public:
    ArcSoftPicZoom();
	~ArcSoftPicZoom();
	
	int32 init();
    void  deinit();
	int32 getBurstCnt();
	int32 processPicZoom(LPASVLOFFSCREEN param);
	int32 enablePicZoom(float scaleRatio);
	int32 disablePicZoom();

private:
	bool startEnhance(LPASVLOFFSCREEN param);
	int32 getMemSize(MUInt32 u32PixelArrayFormat, int width, int height);
	bool dumpImg(MUInt8 *addr, MUInt32 size, char const * const tag, char const * const filetype, int filenum);

private:

	MVoid* mMem;
	MHandle mEnhancer;

	ADZ_INPUTINFO mSrcInput;
	
	ASVLOFFSCREEN mSrcImages[MAX_DZ_INPUT_IMAGES];
	MLong mImageNum; 

	ASVLOFFSCREEN mDstImg;
	ADZ_PARAM mParam;
	MFloat mScale;
};
};
#endif /* ANDROID_ARCSOFT_PIC_ZOOM_H */
