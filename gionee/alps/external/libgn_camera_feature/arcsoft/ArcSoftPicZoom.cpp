/*************************************************************************************
 * 
 * Description:
 * 	Defines ArcSoft APIs for night shot.
 *
 * Author : zhangwu
 * Email  : zhangwu@gionee.com
 * Date   : 2013-09-07
 *
 *************************************************************************************/

#define LOG_TAG "ArcSoftPicZoom"
#include <android/log.h>
#include <string.h>

#include <stdlib.h>
#include <stdio.h>


#include "ArcSoftPicZoom.h"

#define MEM_SIZE 0

namespace android { 

ArcSoftPicZoom::ArcSoftPicZoom()
	: mMem(NULL)
	, mEnhancer(NULL)
	, mImageNum(0)
	, mScale(1.0)
{
	
}

ArcSoftPicZoom::~ArcSoftPicZoom()
{
	
}

int32 
ArcSoftPicZoom::init() 
{
	MRESULT res = 0; 
	
	memset(&mSrcInput, 0, sizeof(mSrcInput));
	memset(&mDstImg, 0, sizeof(mDstImg));
	memset(&mParam, 0, sizeof(mParam));
	memset(&mSrcImages, 0, sizeof(mSrcImages));

	return res;
}

void  
ArcSoftPicZoom::deinit()
{
	ADZ_Uninit(&mEnhancer);

	if(mMem != NULL) {
		mMem = NULL;
	}

	if(mDstImg.ppu8Plane[0] != NULL) {
		MMemFree(NULL, mDstImg.ppu8Plane[0]);
		mDstImg.ppu8Plane[0] = NULL;
	}

	for (int i = 0; i < ((MAX_DZ_INPUT_IMAGES - 1)); i ++) {
		if(mSrcImages[i].ppu8Plane[0] != NULL) {
			free(mSrcImages[i].ppu8Plane[0]);
		}
	}

	memset(&mSrcImages, 0, sizeof(mSrcImages));
	mImageNum = 0;
}

int32
ArcSoftPicZoom::getBurstCnt() 
{
	return MAX_DZ_INPUT_IMAGES;
}

int32 
ArcSoftPicZoom::processPicZoom(LPASVLOFFSCREEN param)
{
	MRESULT res	= 0;
	int memsize	= 0;
	int width	= 0;
    int height	= 0;
	MLong recW	= 0;
	MLong recH	= 0;

	PRINTD("[processPicZoom] mImageNum = %d", mImageNum);

	if (param != NULL && !startEnhance(param)) {
		return res;
	}
	
	width = param->i32Width;
	height = param->i32Height;

	mDstImg.u32PixelArrayFormat	= param->u32PixelArrayFormat;//ASVL_PAF_NV21
	mDstImg.i32Width			= width;
	mDstImg.i32Height			= height;
	
	mDstImg.pi32Pitch[0]		= width;//(width + 3) & 0xfffffffc;
	mDstImg.pi32Pitch[1]		= width;//(width + 3) & 0xfffffffc;

	switch (mDstImg.u32PixelArrayFormat) {
		case ASVL_PAF_NV21:
			memsize 				= mDstImg.pi32Pitch[0] * height + mDstImg.pi32Pitch[1] * (height/2);
			PRINTE("%s memsize = %d", __func__, memsize);
			mDstImg.ppu8Plane[0]	= (MByte*) malloc(memsize);
			mDstImg.ppu8Plane[1] 	= mDstImg.ppu8Plane[0] + mDstImg.pi32Pitch[0] * height;
			break;
		case ASVL_PAF_YUYV:

			break;
		default:	
			//ASVL_PAF_NV21
			memsize 				= mDstImg.pi32Pitch[0] * height + mDstImg.pi32Pitch[1] * (height/2);
			mDstImg.ppu8Plane[0]	= (MByte*) malloc(memsize);
			mDstImg.ppu8Plane[1] 	= mDstImg.ppu8Plane[0] + mDstImg.pi32Pitch[0] * height;
			break;
	}

	recW = (MLong)(param->i32Width / mScale);
	recH = (MLong)(param->i32Height / mScale);

	recW = (recW >> 1) << 1;
	recH = (recH >> 1) << 1;

	ADZ_GetDefaultParam(&mParam);
	mParam.lProcessType = ADZ_PROCESS_TYPE_IMAGE;

	mParam.rtScaleRegion.top 	= ((height - recH) >> 2) << 1;
	mParam.rtScaleRegion.bottom = mParam.rtScaleRegion.top + recH;
	mParam.rtScaleRegion.left 	= (width - recW) >> 2 << 1;
	mParam.rtScaleRegion.right 	= mParam.rtScaleRegion.left + recW;

	mSrcInput.bDualCam = MFalse;
	mSrcInput.lImgNum = MAX_DZ_INPUT_IMAGES;
	
	res = ADZ_Enhancement(mEnhancer, &mSrcInput, &mDstImg, &mParam, NULL, NULL);
	if (res != 0) {
		PRINTE("Failed to process pic zoom [#%ld].", res);
	} else {
		memcpy(param->ppu8Plane[0], mDstImg.ppu8Plane[0], memsize);
	}
	
	for (int i = 0; i < (MAX_DZ_INPUT_IMAGES - 1); i ++) {
		if(mSrcImages[i].ppu8Plane[0] != NULL) {
			free(mSrcImages[i].ppu8Plane[0]);
		}
	}
	
	if(mDstImg.ppu8Plane[0] != NULL) {
		MMemFree(NULL, mDstImg.ppu8Plane[0]);
		mDstImg.ppu8Plane[0] = NULL;
	}

	MMemSet(&mSrcInput, 0, sizeof(mSrcInput));
	MMemSet(&mSrcImages, 0, sizeof(mSrcImages));
	mImageNum = 0;

	PRINTD("process pic zoom over!");

	return res;
}

int32 
ArcSoftPicZoom::enablePicZoom(float scaleRatio)
{
	MRESULT res = 0;

	if (mMem == NULL) {
		res = ADZ_Init(MNull, 0, &mEnhancer);
		if (res != 0) {
			PRINTE("Failed to initialize Pic Zoom enginer [#%ld].", res);
			deinit();
		} else {
			mScale = scaleRatio;
		}
	}

	PRINTE("%s mScale = %f", __func__, mScale);
	
	mImageNum = 0;

	return res;
}

int32 
ArcSoftPicZoom::disablePicZoom()
{
	MRESULT res = 0;

	deinit();

	return res;
}

bool
ArcSoftPicZoom::startEnhance(LPASVLOFFSCREEN param)
{
	bool res = false;
	int memsize = 0;

	memsize = getMemSize(param->u32PixelArrayFormat, param->i32Width, param->i32Height);
	memcpy(&mSrcImages[mImageNum], param, sizeof(ASVLOFFSCREEN));

	if (mImageNum < (MAX_DZ_INPUT_IMAGES)) {
		mSrcImages[mImageNum].ppu8Plane[0] = (MUInt8*) malloc(memsize);
		if (mSrcImages[mImageNum].ppu8Plane[0] == NULL) {
			PRINTE("Failed to malloc memory.");
		} else {
			memcpy(mSrcImages[mImageNum].ppu8Plane[0], param->ppu8Plane[0], memsize);

			mSrcImages[mImageNum].i32Width  = param->i32Width;
			mSrcImages[mImageNum].i32Height = param->i32Height;
			mSrcImages[mImageNum].pi32Pitch[0] = param->i32Width;//(param->i32Width + 3) & 0xfffffffc;
			mSrcImages[mImageNum].pi32Pitch[1] = param->i32Width;//(param->i32Width + 3) & 0xfffffffc;

			switch (param->u32PixelArrayFormat) {
				case ASVL_PAF_NV21:
					mSrcImages[mImageNum].ppu8Plane[1] = mSrcImages[mImageNum].ppu8Plane[0] 
													   + mSrcImages[mImageNum].pi32Pitch[0]*param->i32Height;
					//mSrcImages[mImageNum].ppu8Plane[2] = NULL;
					break;
				case ASVL_PAF_YUYV:
					mSrcImages[mImageNum].ppu8Plane[1] = NULL;
					mSrcImages[mImageNum].ppu8Plane[2] = NULL;
					break;
				default:
					//ASVL_PAF_NV21
					mSrcImages[mImageNum].ppu8Plane[1] = mSrcImages[mImageNum].ppu8Plane[0] 
													   + mSrcImages[mImageNum].pi32Pitch[0]*param->i32Height;
					//mSrcImages[mImageNum].ppu8Plane[2] = NULL;
					break;
			}
		}
	}

	mSrcInput.pImages[mImageNum] = &mSrcImages[mImageNum];

	mImageNum++;
	if (mImageNum >= MAX_DZ_INPUT_IMAGES) {
		res = true;
	} 

	return res;
}

int32 
ArcSoftPicZoom::getMemSize(MUInt32 u32PixelArrayFormat, int width, int height) 
{
	int memSize = 0;

	switch (u32PixelArrayFormat) {
		case ASVL_PAF_NV21:
			memSize = height * width * 3 / 2;
			break;
		case ASVL_PAF_YUYV:
			memSize = height * width * 2;
			break;
		default:	
			//ASVL_PAF_NV21
			memSize = height * width * 3 / 2;
			break;
	}

	return memSize;
}

bool 
ArcSoftPicZoom::
dumpImg(MUInt8 *addr, MUInt32 size, char const * const tag, char const * const filetype, int filenum)
{
    
	char fileName[64] = {0};

    sprintf(fileName, "/data/%s_%d.%s", tag, filenum, filetype);
	
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

