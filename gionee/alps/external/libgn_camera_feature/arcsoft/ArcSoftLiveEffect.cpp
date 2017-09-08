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

#define LOG_TAG "ArcSoftLiveEffect"
#include <android/log.h>
#include <string.h>
#include <time.h>

#include "GNCameraFeatureDbgTime.h"
#include "ArcSoftLiveEffect.h"

#define MASK_PATH	"/system/etc/gn_camera_feature/arcsoft/maskfile/"

namespace android { 

ArcSoftLiveEffect::ArcSoftLiveEffect()
	: mEffectID(-1)
{

}

ArcSoftLiveEffect::~ArcSoftLiveEffect()
{
	
}

int32 
ArcSoftLiveEffect::init()
{
	MRESULT res = 0; 

	return res;
}

void  
ArcSoftLiveEffect::deinit()
{
	mEffectID = -1;
}

int32 
ArcSoftLiveEffect::setLiveEffectType(GNLiveEffect_t type)
{
	MRESULT res = 0; 

	mEffectID = getEffectID(type);
	if (mEffectID == -1) {
		PRINTE("Can't support the effect type[%d]", type);
		res = -1;
	}

	return res;
}

int32 
ArcSoftLiveEffect::processLiveEffect(LPASVLOFFSCREEN param, bool isMirror)
{
	MRESULT res = 0;
	MHandle handle = NULL;
	MEffectParam effectPara = {0};
	MBITMAP srcBitmap = {0};
	MBITMAP dstBitmap = {0};
	MPixelInfo pixelInfo = {0};
	GNCameraFeatureDbgTime dbgTime;
	CosmetologyBackligntParam cbParam;
	
	if (mEffectID == -1) {
		return -1;
	}

	//Set effect parameter
	effectPara.dwEffectID = mEffectID;

	if (mEffectID == MEID_COSMETOLOGY_BACKLIGHT) {
		cbParam.lDermabrasionSize 		= 11;
		cbParam.dDermabrasionStrength 	= 6;
		cbParam.lWhiteningStrength 		= 25;

		effectPara.dwParamSize 	= sizeof(cbParam);
		effectPara.pEffect 		= &cbParam;
	} else {
		effectPara.dwParamSize 	= 0;
		effectPara.pEffect 		= NULL;
	}

	if (isMirror) {
		effectPara.dwDirection = MDIRECTION_FLIP_HORIZONTAL;
	}

	//Set pixcel Information
	pixelInfo.dwPixelArrayFormat = param->u32PixelArrayFormat;
	pixelInfo.lWidth = param->i32Width;
	pixelInfo.lHeight = param->i32Height;

	res = MIPCreateImageEngine(MASK_PATH, &effectPara, &pixelInfo, &handle);
	if (res != 0) {
		PRINTE("Failed to initialized the Filter Engineer[%d].", res);
	} else {
		res = MIPDoEffect(handle, param);
		if (res != 0) {
			PRINTE("Failed to handle Filter[%d].", res);
		}
	}
	
	if (handle != NULL) {
		MIPDestroyImageEngine(handle);
		handle = NULL;
	}

	dbgTime.print(__func__);

	return res;
}

int32 
ArcSoftLiveEffect::getEffectID(GNLiveEffect_t type)
{
	int32 ret = -1;

	switch (type) {
		case GN_LIVE_EFFECT_FLEETINGTIME:
			ret = MEID_FLEETINGTIME;
			break;
		case GN_LIVE_EFFECT_CRAYON:
			ret = MEID_CRAYON;
			break;
		case GN_LIVE_EFFECT_SNOWFLAKES:
			ret = MEID_SNOWFLAKES;
			break;
		case GN_LIVE_EFFECT_LIGHTBEAM:
			ret = MEID_LIGHTBEAM;
			break;
		case GN_LIVE_EFFECT_REFLECTION:
			ret = MEID_REFLECTION;
			break;
		case GN_LIVE_EFFECT_SUNSET:
			ret = MEID_SUNSET;
			break;
		case GN_LIVE_EFFECT_REVERSAL:
			ret = MEID_REVERSAL;
			break;
		case GN_LIVE_EFFECT_WARMLOMO:
			ret = MEID_WARMLOMO;
			break;
		case GN_LIVE_EFFECT_COLDLOMO:
			ret = MEID_COLDLOMO;
			break;
		case GN_LIVE_EFFECT_SOFTPINK:
			ret = MEID_SOFTPINK;
			break;
		case GN_LIVE_EFFECT_JAPANBACKLIGHT:
			ret = MEID_JAPANBACKLIGHT;
			break;
		case GN_LIVE_EFFECT_COSMETOLOGY_BACKLIGHT:
			ret = MEID_COSMETOLOGY_BACKLIGHT;
			break;
		case GN_LIVE_EFFECT_FINEFOOD:
			ret = MEID_FINEFOOD;
			break;
		case GN_LIVE_EFFECT_BLACKWHITE:
			ret = MEID_BLACK_WHITE;
			break;
		default:
			break;
	}

	return ret;
}

};
