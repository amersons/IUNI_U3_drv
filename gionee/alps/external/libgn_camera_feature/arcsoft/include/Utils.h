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
* Utils.h
*
* Reference:
*
* Description:
*
* Create by twj8434 2013-3-15
*
*/

#ifndef __UTILSH__
#define __UTILSH__

#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <sys/syscall.h>

#include "amcomdef.h"
#include "asvloffscreen.h"

#define		SAFE_MEM_FREE(MEM)		if (MNull != MEM) {free(MEM); MEM = MNull;}
#define		SAFE_MEM_DEL(MEM)		if (MNull != MEM) {delete MEM; MEM = MNull;}
#define		SAFE_MEMARR_DEL(MEM)	if (MNull != MEM) {delete[] MEM; MEM = MNull;}

#define		SAFE_LOCALREF_DEL(REF)	if (MNull != REF) {env->DeleteLocalRef(REF); REF = MNull;}
#define		SAFE_GLOBALREF_DEL(REF)	if (MNull != REF) {env->DeleteGlobalRef(REF); REF = MNull;}

#define		getThreadId()	syscall(__NR_gettid)

long gettime();

int saveDataToFile(const char* pFileFullPath, const char* pData, const int iSize);

void buildAsvlOffScreen(unsigned char* pData,LPASVLOFFSCREEN pAsvlOffScreen);

#endif	//end of __UTILSH__