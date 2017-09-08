/********************************************************************************
 *	SRS Labs CONFIDENTIAL
 *	@Copyright 2010 by SRS Labs.
 *	All rights reserved.
 *
 *  Description:
 *  Exposes all srs_hardlimiter APIs
 *
 *	Author: Zesen Zhuang
 *
 *  RCS keywords:
 *	$Id: //srstech/srs_hardlimiter/std_fxp/include/srs_hardlimiter_api.h#10 $
 *  $Author: oscarh $
 *  $Date: 2010/11/16 $
 *	
********************************************************************************/

#ifndef __SRS_HARDLIMITER_API_H__
#define __SRS_HARDLIMITER_API_H__

#include "srs_hardlimiter_def.h"


#ifdef __cplusplus
extern "C"{
#endif /*__cplusplus*/

//API declaration here:

int			SRS_HdLmt_GetObjSize();
SRSResult	SRS_HdLmt_CreateObj(SRSHdLmtObj *pObj, void* pBuf, SRS_Allocator alloc, void *pContext);

/* init and configuration APIs */
SRSResult	SRS_HdLmt_InitObj(SRSHdLmtObj hlObj);

/* main APIs */
SRSResult	SRS_HdLmt_Process(SRSHdLmtObj hlObj, SRSStereoCh *input, SRSStereoCh *output, int blockFrames, void *ws);


void		SRS_HdLmt_SetControlDefaults(SRSHdLmtObj hlObj);

//"Set" functions:
void		SRS_HdLmt_SetEnable(SRSHdLmtObj hlObj, SRSBool enable);
SRSResult	SRS_HdLmt_SetInputGain(SRSHdLmtObj hlObj, SRSInt16 gain);	//I16.3	 0.0-4.0
SRSResult	SRS_HdLmt_SetOutputGain(SRSHdLmtObj hlObj, SRSInt16 gain);	//I16.3	 0.0-4.0
SRSResult	SRS_HdLmt_SetBypassGain(SRSHdLmtObj hlObj, SRSInt16 gain);	//I16.1	 0.0-1.0
SRSResult	SRS_HdLmt_SetDelayLen(SRSHdLmtObj hlObj, int lenSamples);
SRSResult	SRS_HdLmt_SetBoostGain(SRSHdLmtObj hlObj, SRSInt32 boostGain);		//I32.6	 0.001-32.0
SRSResult	SRS_HdLmt_SetLimitLevel(SRSHdLmtObj hlObj, SRSInt16 limitLevel);		//I16.1	 0.0-1.0

//"Get" functions:
SRSBool		SRS_HdLmt_GetEnable(SRSHdLmtObj hlObj);
SRSInt16	SRS_HdLmt_GetInputGain(SRSHdLmtObj hlObj);		//I16.3	 0.0-4.0
SRSInt16	SRS_HdLmt_GetOutputGain(SRSHdLmtObj hlObj);		//I16.3	 0.0-4.0
SRSInt16	SRS_HdLmt_GetBypassGain(SRSHdLmtObj hlObj);		//I16.1	 0.0-1.0
int			SRS_HdLmt_GetDelayLen(SRSHdLmtObj hlObj);
SRSInt32	SRS_HdLmt_GetBoostGain(SRSHdLmtObj hlObj);		//I32.9	 0.001-256.0
SRSInt16	SRS_HdLmt_GetLimitLevel(SRSHdLmtObj hlObj);		//I16.1	 0.0-1.0

/* version info query function */
unsigned char	SRS_HdLmt_GetTechVersion(SRSVersion which);
unsigned char	SRS_HdLmt_GetLibVersion(SRSVersion which);

/* the following APIs are added to add flexability of hl IP for SRS internal use only*/
SRSInt32	SRS_HdLmt_GetLCoef(SRSHdLmtObj hlObj);
SRSResult	SRS_HdLmt_SetLCoef(SRSHdLmtObj hlObj, SRSInt32 lmtcoef);

SRSInt32	SRS_HdLmt_GetHLThresh(SRSHdLmtObj hlObj);
SRSResult	SRS_HdLmt_SetHLThresh(SRSHdLmtObj hlObj, SRSInt32 hlthresh);



#ifdef __cplusplus
}
#endif /*__cplusplus*/


#endif /*__SRS_HARDLIMITER_API_H__*/