/*************************************************************************************
 * 
 * Description:
 * 	Defines common variables.
 *
 * Author : wutangzhi
 * Email  : wutz@gionee.com
 * Date   : 2012-06-11
 *
 *************************************************************************************/
 
#ifndef SCALADO_CAMERA_FEATURE_DEFS_H
#define SCALADO_CAMERA_FEATURE_DEFS_H

#define LOG_TAG "ScaladoCameraFeature"
#if 1
#include <android/log.h>

#define XLOGI(fmt, args...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, fmt, ##args)
#define XLOGD(fmt, args...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, fmt, ##args)
#define XLOGE(fmt, args...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, fmt, ##args) 

#define PRINTE_RES(value, res)	\
	XLOGE("%s [%d line] : %s #%d", __func__, __LINE__, value, SCB_GET_VALUE(res))
#define PRINTE(value)	\
	XLOGE("%s [%d line] : %s ", __func__, __LINE__, value)
#define PRINTD(...) \
	XLOGE(__VA_ARGS__)
#else
#include <cutils/log.h>	
#define PRINTE_RES(value, res)	\
	LOGE("%s [%d line] : %s #%d", __func__, __LINE__, value, SCB_GET_VALUE(res))
#define PRINTE(value)	\
	LOGE("%s [%d line] : %s ", __func__, __LINE__, value)
#define PRINTD(...) \
	LOGE(__VA_ARGS__)
#endif

#include "scbdefs.h"
#include "scberror.h"

#define WARP_PATH(filename)			"/system/etc/gn_camera_feature/scalado/warp/"#filename
#define WARP_WARP_FISHEYE_FILENAME	WARP_PATH(fisheye.wrp)
#define WARP_ALIENSCUM_FILENAME		WARP_PATH(alienscum.wrp)
#define WARP_BENCHMARK_FILENAME		WARP_PATH(benchmark.wrp)
#define WARP_BIGBUPPA_FILENAME		WARP_PATH(bigbuppa.wrp)
#define WARP_BOOZIEBOWL_FILENAME	WARP_PATH(booziebowl.wrp)
#define WARP_CONEHEAD_FILENAME		WARP_PATH(conehead.wrp)
#define WARP_FUNKYFRESH_FILENAME	WARP_PATH(funkyfresh.wrp)
#define WARP_JELLYBELLY_FILENAME	WARP_PATH(jellybelly.wrp)
#define WARP_PETTYPETIT_FILENAME	WARP_PATH(pettypetit.wrp)
#define WARP_EYEBALLEDEVY_FILENAME	WARP_PATH(eyeballedevy.wrp)
#define WARP_SPEEDYWEED_FILENAME	WARP_PATH(speedyweed.wrp)

/* IGNORE_FRAME_INDEX is the index of normal frame,  which value is defined according to HAL  */
#define HDR_NORMAL_IMAGE_INDEX		1
#define LOWLIGHT_NORMAL_IMAGE_INDEX 3

#define HDR_BURST_CNT				3
#define LOWLIGHT_BURST_CNT  		4

#define PANORAMA_OVERLAP			55
#define PANORAMA_DIRECTION_TRIGGER	0
#define PANORAMA_OFFSET_MAX			20
#define TARGET_DISTANCE_HORIZONTAL	160
#define TARGET_DISTANCE_VERTICAL	120

#define PANORAMA_NUM_MAX			10

#endif /* SCALADO_CAMERA_FEATURE_DEFS_H */

