/*----------------------------------------------------------------------------------------------
*
* This file is ArcSoft's property. It contains ArcSoft's trade secret, proprietary and
* confidential information.
*
* The information and code contained in this file is only for authorized ArcSoft employees
* to design, create, modify, or review.
*
* DO NOT DISTRIBUTE, DO NOT DUPLICATE OR TRANSMIT IN ANY FORM WITHOUT PROPER AUTHORIZATION.
*
* If you are not an intended recipient of this file, you must not copy, distribute, modify,
* or take any action in reliance on it.
*
* If you have received this file in error, please immediately notify ArcSoft and
* permanently delete the original and any copy of any file and any printout thereof.
*
*-------------------------------------------------------------------------------------------------*/
/*
* JniCommon.h
*
* Reference:
*
* Description:
*
* Create by twj8434 2013-3-13
*
*/

#ifndef __JNICOMMONH__
#define __JNICOMMONH__

#include <android/log.h>

#define  LOG_TAG					"Arcsoft"
#define  LOGI(...)					__android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)					__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define  LOGD(...)					__android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGV(...)					__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)

#define JNI_LOG		//if this macro be defined, log will be print.

#ifdef JNI_LOG
#define LOGCATE LOGE
#define LOGCATD LOGD
#define LOGCATV LOGV

#define ENTER_FUNCTION	LOGCATV("%s:%s <---", __FILE__, __FUNCTION__);
#define EXIT_FUNCTION	LOGCATV("%s:%s --->", __FILE__, __FUNCTION__);

#else
#define LOGCATE
#define LOGCATD
#define LOGCATV

#define ENTER_FUNCTION
#define EXIT_FUNCTION
#endif	//end of JNI_LOG

#define JNI_TIME		//if JNI_TIME be defined, function cost time will be print.

#ifdef JNI_TIME
#define LOGTIME LOGD
#define BEGIN_TIME {\
		long t0 = gettime();
#define END_TIME(FUN) \
		LOGTIME("%s:%s cost time %dms", __FILE__, FUN, gettime()-t0);}
#else
#define BEGIN_TIME
#define END_TIME(FUN)
#endif	//end of JNI_TIME

#endif	//end of __JNICOMMONH__