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

#define LOG_TAG "ArcSoftNightShot"
#include <android/log.h>
#include <string.h>

#include "ArcSoftNightShot.h"

#define MEM_SIZE	(10 * 1024 * 1024)	//10M

namespace android { 

ArcSoftNightShot::ArcSoftNightShot()
	: mMem(NULL)
	, mMemMgr(NULL)
	, mEnhancer(NULL)
	, mImageNum(0)
{
	
}
	
int32 
ArcSoftNightShot::init() 
{
	MRESULT res = 0; 
	
	memset(&mSrcInput, 0, sizeof(mSrcInput));
	memset(&mDstImg, 0, sizeof(mDstImg));
	memset(&mParam, 0, sizeof(mParam));
	memset(&mSrcImages, 0, sizeof(mSrcImages));

	return res;
}
void  
ArcSoftNightShot::deinit()
{
	ANS_Uninit(&mEnhancer);

	if(mMemMgr != NULL) {
		MMemMgrDestroy(mMemMgr);
		mMemMgr = NULL;
	}

	if(mMem != NULL) {
		MMemFree(NULL, mMem);
		mMem = NULL;
	}

	if(mDstImg.ppu8Plane[0] != NULL) {
		MMemFree(NULL, mDstImg.ppu8Plane[0]);
		mDstImg.ppu8Plane[0] = NULL;
	}

	for (int i = 0; i < ((MAX_INPUT_IMAGES - 1)); i ++) {
		if(mSrcImages[i].ppu8Plane[0] != NULL) {
			free(mSrcImages[i].ppu8Plane[0]);
		}
	}

	memset(&mSrcImages, 0, sizeof(mSrcImages));
	mImageNum = 0;
}

int32
ArcSoftNightShot::getBurstCnt() 
{
	return MAX_INPUT_IMAGES;
}

int32 
ArcSoftNightShot::processNightShot(LPASVLOFFSCREEN param)
{
	MRESULT res = 0;
	int memsize = 0;
	int yStride = 0;
    int yScanline = 0;
    int uvStride = 0;
    int uvScanlie = 0;

	PRINTD("[processNightShot] mImageNum = %d", mImageNum);

	if (param != NULL && !startEnhance(param)) {
		return res;
	}

	if (ALIGN_FORMAT != ALIGN_TO_32) {
		yStride = ALIGN_TO_SIZE(param->i32Width, ALIGN_FORMAT);
		yScanline = ALIGN_TO_SIZE(param->i32Height, ALIGN_FORMAT);
	} else {
		yStride = param->i32Width;
		yScanline = param->i32Height;
	}
	
	mDstImg.i32Height 			= param->i32Height;
	mDstImg.i32Width			= param->i32Width;
	mDstImg.u32PixelArrayFormat	= param->u32PixelArrayFormat;
	mDstImg.pi32Pitch[0]		= param->pi32Pitch[0];
	mDstImg.pi32Pitch[1]		= param->pi32Pitch[1];
	mDstImg.pi32Pitch[2]		= param->pi32Pitch[2];

	switch (mDstImg.u32PixelArrayFormat) {
		case ASVL_PAF_NV21:
			memsize 				= yStride * yScanline * 3 / 2;
			mDstImg.ppu8Plane[0]	= (MByte*)MMemAlloc(NULL, memsize);
			mDstImg.ppu8Plane[1] 	= mDstImg.ppu8Plane[0] + yStride * yScanline;
			mDstImg.ppu8Plane[2] 	= NULL;
			break;
		case ASVL_PAF_YUYV:
			memsize 				= yStride * yScanline * 2;
			mDstImg.ppu8Plane[0]	= (MByte*)MMemAlloc(NULL, memsize);
			mDstImg.ppu8Plane[1] 	= NULL;
			mDstImg.ppu8Plane[2] 	= NULL;
			break;
		default:	
			//ASVL_PAF_NV21
			memsize 				= yStride * yScanline * 3 / 2;
			mDstImg.ppu8Plane[0]	= (MByte*)MMemAlloc(NULL, memsize);
			mDstImg.ppu8Plane[1] 	= mDstImg.ppu8Plane[0] + yStride * yScanline;
			mDstImg.ppu8Plane[2] 	= NULL;
			break;
	}

	res = ANS_Enhancement(mEnhancer, &mSrcInput, &mDstImg, &mParam, NULL, NULL);
	if (res != 0) {
		PRINTE("Failed to process night shot [#%ld].", res);
	} else {
		memcpy(param->ppu8Plane[0], mDstImg.ppu8Plane[0], memsize);
	}

	for (int i = 0; i < (MAX_INPUT_IMAGES - 1); i ++) {
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

	PRINTD("process night shot over!");

	return res;
}

int32 
ArcSoftNightShot::enableNightShot()
{
	MRESULT res = 0;

	if (mMem == NULL) {
		mMem = MMemAlloc(NULL, MEM_SIZE);
		mMemMgr = MMemMgrCreate(mMem, MEM_SIZE);

		res = ANS_Init(mMemMgr, &mEnhancer);
		if (res != 0) {
			PRINTE("Failed to initialize nightshot enginer [#%ld].", res);
			deinit();
		} else {
			ANS_GetDefaultParam(&mParam);
		}
	}

	mImageNum = 0;

	return res;
}

int32 
ArcSoftNightShot::disableNightShot()
{
	MRESULT res = 0;

	deinit();

	return res;
}

bool
ArcSoftNightShot::startEnhance(LPASVLOFFSCREEN param)
{
	bool res = false;
	int memsize = 0;
	int yStride = 0;
    int yScanline = 0;
	int uvStride = 0;
	int uvScanlie = 0;

	if (ALIGN_FORMAT != ALIGN_TO_32) {
		yStride = ALIGN_TO_SIZE(param->i32Width, ALIGN_FORMAT);
		yScanline = ALIGN_TO_SIZE(param->i32Height, ALIGN_FORMAT);
		uvStride = ALIGN_TO_SIZE(param->i32Width, ALIGN_FORMAT);
		uvScanlie = ALIGN_TO_SIZE(yScanline / 2, ALIGN_FORMAT);
	} else {
		yStride = param->i32Width;
		yScanline = param->i32Height;
		uvStride = param->i32Width;
		uvScanlie = param->i32Height / 2;
	}

	memsize = getMemSize(param->u32PixelArrayFormat, yStride, yScanline);
	memcpy(&mSrcImages[mImageNum], param, sizeof(ASVLOFFSCREEN));

	if (mImageNum < (MAX_INPUT_IMAGES - 1)) {
		mSrcImages[mImageNum].ppu8Plane[0] = (MUInt8*) malloc(memsize);
		if (mSrcImages[mImageNum].ppu8Plane[0] == NULL) {
			PRINTE("Failed to malloc memory.");
		} else {
			memcpy(mSrcImages[mImageNum].ppu8Plane[0], param->ppu8Plane[0], memsize);

			switch (param->u32PixelArrayFormat) {
				case ASVL_PAF_NV21:
					mSrcImages[mImageNum].pi32Pitch[0] = yStride;
					mSrcImages[mImageNum].pi32Pitch[1] = uvStride;
					mSrcImages[mImageNum].pi32Pitch[2] = 0;
					mSrcImages[mImageNum].ppu8Plane[1] = mSrcImages[mImageNum].ppu8Plane[0] + yStride * yScanline;
					mSrcImages[mImageNum].ppu8Plane[2] = NULL;
					break;
				case ASVL_PAF_YUYV:
					mSrcImages[mImageNum].pi32Pitch[0] = yStride*2;
					mSrcImages[mImageNum].pi32Pitch[1] = 0;
					mSrcImages[mImageNum].pi32Pitch[2] = 0;
					mSrcImages[mImageNum].ppu8Plane[1] = NULL;
					mSrcImages[mImageNum].ppu8Plane[2] = NULL;
					break;
				default:
					//ASVL_PAF_NV21
					mSrcImages[mImageNum].pi32Pitch[0] = yStride;
					mSrcImages[mImageNum].pi32Pitch[1] = uvStride;
					mSrcImages[mImageNum].pi32Pitch[2] = 0;
					mSrcImages[mImageNum].ppu8Plane[1] = mSrcImages[mImageNum].ppu8Plane[0] + yStride * yScanline;
					mSrcImages[mImageNum].ppu8Plane[2] = NULL;
					break;
			}
		}
	}

	mSrcInput.lImgNum = mImageNum;
	mSrcInput.pImages[mImageNum] = &mSrcImages[mImageNum];
	
	mImageNum++;
	if (mImageNum >= MAX_INPUT_IMAGES) {
		res = true;
	} 

	return res;
}

int32 
ArcSoftNightShot::getMemSize(MUInt32 u32PixelArrayFormat, int width, int height) 
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

};

