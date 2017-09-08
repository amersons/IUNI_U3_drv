/********************************************************************************
 *	SRS Labs CONFIDENTIAL
 *	@Copyright 2010 by SRS Labs.
 *	All rights reserved.
 *
 *  Description:
 *  Exposes all srs_wowhd APIs
 *
 *	Author: Zesen Zhuang
 *
 *  RCS keywords:
 *	$Id: //srstech/srs_wowhd/std_fxp/include/srs_wowhd_api.h#6 $
 *  $Author: oscarh $
 *  $Date: 2010/12/17 $
 *	
********************************************************************************/

#ifndef __SRS_WOWHD_API_H__
#define __SRS_WOWHD_API_H__

#include "srs_wowhd_def.h"
#include "srs_fxp.h"


#ifdef __cplusplus
extern "C"{
#endif /*__cplusplus*/

//API declaration here:

int				SRS_WOWHD_GetObjSize();
SRSResult		SRS_WOWHD_CreateObj(SRSWowhdObj *pObj, void* pBuf, SRS_Allocator alloc,void* pContext);

SRSResult		SRS_WOWHD_InitObj8k(SRSWowhdObj wowhdObj);
SRSResult		SRS_WOWHD_InitObj11k(SRSWowhdObj wowhdObj);
SRSResult		SRS_WOWHD_InitObj16k(SRSWowhdObj wowhdObj);
SRSResult		SRS_WOWHD_InitObj22k(SRSWowhdObj wowhdObj);
SRSResult		SRS_WOWHD_InitObj24k(SRSWowhdObj wowhdObj);
SRSResult		SRS_WOWHD_InitObj32k(SRSWowhdObj wowhdObj);
SRSResult		SRS_WOWHD_InitObj44k(SRSWowhdObj wowhdObj);
SRSResult		SRS_WOWHD_InitObj48k(SRSWowhdObj wowhdObj);
SRSResult		SRS_WOWHD_InitObj88k(SRSWowhdObj wowhdObj);
SRSResult		SRS_WOWHD_InitObj96k(SRSWowhdObj wowhdObj);


SRSResult		SRS_WOWHD_Process(SRSWowhdObj wowhdObj, SRSStereoCh *input, SRSStereoCh *output, int blockSize, void *ws);

void			SRS_WOWHD_SetControlDefaults(SRSWowhdObj wowhdObj);

//Get/Set function with structural paras:
void			SRS_WOWHD_GetControls(SRSWowhdObj wowhdObj, SRSWowhdControls *pCtrls);
void			SRS_WOWHD_GetTBHDControls(SRSWowhdObj wowhdObj, SRSWowhdTBHDControls *pCtrls);
void			SRS_WOWHD_GetSRS3DControls(SRSWowhdObj wowhdObj, SRSWowhdSRS3DControls *pCtrls);

SRSResult		SRS_WOWHD_SetControls(SRSWowhdObj wowhdObj, const SRSWowhdControls *pCtrls);
SRSResult		SRS_WOWHD_SetTBHDControls(SRSWowhdObj wowhdObj, const SRSWowhdTBHDControls *pCtrls);
SRSResult		SRS_WOWHD_SetSRS3DControls(SRSWowhdObj wowhdObj, const SRSWowhdSRS3DControls *pCtrls);

//"Set" functions:
void			SRS_WOWHD_SetEnable(SRSWowhdObj wowhdObj, SRSBool enable);
SRSResult		SRS_WOWHD_SetInputGain(SRSWowhdObj wowhdObj, SRSInt16 gain);	//I16.1 0.0-1.0
SRSResult		SRS_WOWHD_SetOutputGain(SRSWowhdObj wowhdObj, SRSInt16 gain);	//I16.1 0.0-1.0
SRSResult		SRS_WOWHD_SetBypassGain(SRSWowhdObj wowhdObj, SRSInt16 gain);	//I16.1 0.0-1.0

/* srs3d sub component */
void			SRS_WOWHD_SetSRS3DEnable(SRSWowhdObj wowhdObj, SRSBool enable);
SRSResult		SRS_WOWHD_SetSRS3DSpaceLevel(SRSWowhdObj wowhdObj, SRSInt16 level);	//0.0-1.0
SRSResult		SRS_WOWHD_SetSRS3DCenterLevel(SRSWowhdObj wowhdObj, SRSInt16 level);	//0.0-1.0
void			SRS_WOWHD_SetSRS3DHeadphoneEnable(SRSWowhdObj wowhdObj, SRSBool enable);  //Enable headphone process mode
void			SRS_WOWHD_SetSRS3DHighBitRateEnable(SRSWowhdObj wowhdObj, SRSBool enable);//enable high bit rate process
SRSResult		SRS_WOWHD_SetSRS3DMode(SRSWowhdObj wowhdObj, SRSSrs3DMode mode);

/* trubass sub component */
void			SRS_WOWHD_SetTBEnable(SRSWowhdObj wowhdObj, SRSBool enable);
SRSResult		SRS_WOWHD_SetTBLevel(SRSWowhdObj wowhdObj, SRSInt16 level);
SRSResult		SRS_WOWHD_SetTBSpeakerSize(SRSWowhdObj wowhdObj, SRSTBHDSpeakerSize sz);
SRSResult		SRS_WOWHD_SetTBCustomSpeakerFilterCoefs(SRSWowhdObj wowhdObj, const SRSInt32 *coefs); //Set custom speaker coefficients
void			SRS_WOWHD_SetTBSplitAnalysisEnable(SRSWowhdObj wowhdObj, SRSBool enable);				//disabled by default
SRSResult		SRS_WOWHD_SetTBMode(SRSWowhdObj wowhdObj, SRSTBHDMode mode);
SRSResult		SRS_WOWHD_SetTBCompressorLevel(SRSWowhdObj wowhdObj, SRSInt16 level); //TB compressor level, 0~1.0, default 0.25, I16.SRS_TBHD_CTRL_IWL

/* definition sub component */
void		SRS_WOWHD_SetDefEnable(SRSWowhdObj wowhdObj, SRSBool enable);
SRSResult	SRS_WOWHD_SetDefLevel(SRSWowhdObj wowhdObj, SRSInt16 level);

/* focus sub component */
void		SRS_WOWHD_SetFocusEnable(SRSWowhdObj wowhdObj, SRSBool enable);
SRSResult	SRS_WOWHD_SetFocusLevel(SRSWowhdObj wowhdObj, SRSInt16 level);

/* limiter sub component */
SRSResult	SRS_WOWHD_SetLimiterMinimalGain(SRSWowhdObj wowhdObj, SRSInt32 minGain);	//i32.2
void		SRS_WOWHD_SetLimiterEnable(SRSWowhdObj wowhdObj, SRSBool enable);


//"Get" functions:
SRSBool		SRS_WOWHD_GetEnable(SRSWowhdObj wowhdObj);
SRSInt16	SRS_WOWHD_GetInputGain(SRSWowhdObj wowhdObj);
SRSInt16	SRS_WOWHD_GetOutputGain(SRSWowhdObj wowhdObj);
SRSInt16	SRS_WOWHD_GetBypassGain(SRSWowhdObj wowhdObj);

/* srs3d sub component */
SRSBool			SRS_WOWHD_GetSRS3DEnable(SRSWowhdObj wowhdObj);
SRSInt16		SRS_WOWHD_GetSRS3DSpaceLevel(SRSWowhdObj wowhdObj);
SRSInt16		SRS_WOWHD_GetSRS3DCenterLevel(SRSWowhdObj wowhdObj);
SRSBool			SRS_WOWHD_GetSRS3DHeadphoneEnable(SRSWowhdObj wowhdObj);
SRSBool			SRS_WOWHD_GetSRS3DHighBitRateEnable(SRSWowhdObj wowhdObj);
SRSSrs3DMode	SRS_WOWHD_GetSRS3DMode(SRSWowhdObj wowhdObj);

/* trubass sub component */
SRSBool						SRS_WOWHD_GetTBEnable(SRSWowhdObj wowhdObj);
SRSInt16					SRS_WOWHD_GetTBLevel(SRSWowhdObj wowhdObj);						//I16.SRS_STB_CTRL_IWL
SRSTBHDSpeakerSize			SRS_WOWHD_GetTBSpeakerSize(SRSWowhdObj wowhdObj);
SRSTBHDMode					SRS_WOWHD_GetTBMode(SRSWowhdObj wowhdObj);
SRSTBHDCustomSpeakerCoefs	SRS_WOWHD_GetTBCustomSpeakerFilterCoefs(SRSWowhdObj wowhdObj); 
SRSBool						SRS_WOWHD_GetTBSplitAnalysisEnable(SRSWowhdObj wowhdObj);
SRSInt16					SRS_WOWHD_GetTBCompressorLevel(SRSWowhdObj wowhdObj);

/* definition sub component */
SRSBool		SRS_WOWHD_GetDefEnable(SRSWowhdObj wowhdObj);
SRSInt16	SRS_WOWHD_GetDefLevel(SRSWowhdObj wowhdObj);

/* focus sub component */
SRSBool		SRS_WOWHD_GetFocusEnable(SRSWowhdObj wowhdObj);
SRSInt16	SRS_WOWHD_GetFocusLevel(SRSWowhdObj wowhdObj);

/* limiter sub component */
SRSInt32	SRS_WOWHD_GetLimiterMinimalGain(SRSWowhdObj wowhdObj);
SRSBool		SRS_WOWHD_GetLimiterEnable(SRSWowhdObj wowhdObj);

//Version query:
unsigned char				SRS_WOWHD_GetTechVersion(SRSVersion which);
unsigned char				SRS_WOWHD_GetLibVersion(SRSVersion which);

const SRSLibInfo*			SRS_WOWHD_GetLibsInfo();

#ifdef __cplusplus
}
#endif /*__cplusplus*/


#endif /*__SRS_WOWHD_API_H__*/
