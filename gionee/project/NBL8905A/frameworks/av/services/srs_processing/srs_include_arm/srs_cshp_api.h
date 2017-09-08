/********************************************************************************
 *	SRS Labs CONFIDENTIAL
 *	@Copyright 2010 by SRS Labs.
 *	All rights reserved.
 *
 *  Description:
 *  Exposes all srs_cshp APIs
 *
 *  RCS keywords:
 *	$Id: //srstech/srs_cshp/std_fxp/include/srs_cshp_api.h#7 $
 *  $Author: oscarh $
 *  $Date: 2010/11/16 $
 *	
********************************************************************************/

#ifndef __SRS_CSHP_API_H__
#define __SRS_CSHP_API_H__

#include "srs_cshp_def.h"


#ifdef __cplusplus
extern "C"{
#endif /*__cplusplus*/

int			SRS_CSHP_GetObjSize();
SRSResult	SRS_CSHP_CreateObj(SRSCshpObj *pObj, void *pBuf, SRS_Allocator alloc, void *pContext);

void		SRS_CSHP_SetControlDefaults(SRSCshpObj cshpObj);

SRSResult	SRS_CSHP_InitObj16k(SRSCshpObj cshpObj);
SRSResult	SRS_CSHP_InitObj22k(SRSCshpObj cshpObj);
SRSResult	SRS_CSHP_InitObj24k(SRSCshpObj cshpObj);
SRSResult	SRS_CSHP_InitObj32k(SRSCshpObj cshpObj);
SRSResult	SRS_CSHP_InitObj44k(SRSCshpObj cshpObj);
SRSResult	SRS_CSHP_InitObj48k(SRSCshpObj cshpObj);



SRSResult	SRS_CSHP_Process(SRSCshpObj cshpObj, SRSStereoCh *audioIO, int blockFrames, void *ws); //stereo audio processing
SRSResult	SRS_CSHP_Process_5P1(SRSCshpObj cshpObj, SRS5Point1Ch *audioIn, SRSStereoCh *audioOut, int blockFrames, void *ws); //5.1 input, stereo output processing

//Set/Get functions with structure parameters:
SRSResult	SRS_CSHP_SetControls(SRSCshpObj cshpObj, const SRSCshpControls *pCtrls); //Set all CSHP controls
SRSResult	SRS_CSHP_SetTruBassControls(SRSCshpObj cshpObj, const SRSCshpTruBassControls *pCtrls); //Set TBHD controls

void		SRS_CSHP_GetControls(SRSCshpObj cshpObj, SRSCshpControls *pCtrls);
void		SRS_CSHP_GetTruBassControls(SRSCshpObj cshpObj, SRSCshpTruBassControls *pCtrls);

SRSResult	SRS_CSHP_SetTruBassCustomSpeakerFilterCoefs(SRSCshpObj cshpObj, const SRSInt32 *coefs); //Set custom speaker coefficients

//"Set" functions:
void				SRS_CSHP_SetEnable(SRSCshpObj cshpObj, SRSBool enable);
SRSResult			SRS_CSHP_SetInputGain(SRSCshpObj cshpObj, SRSInt16 gain);	//I16.1
SRSResult			SRS_CSHP_SetOutputGain(SRSCshpObj cshpObj, SRSInt16 gain);	//I16.1
SRSResult			SRS_CSHP_SetBypassGain(SRSCshpObj cshpObj, SRSInt16 gain);	//I16.1
SRSResult			SRS_CSHP_SetRenderingMode(SRSCshpObj cshpObj, SRSCshpRenderingMode mode);

//CSDecoder:
SRSResult			SRS_CSHP_SetCSDecoderProcMode(SRSCshpObj cshpObj, SRSCSDProcMode mode);

//Focus (DialogClarity):
void				SRS_CSHP_SetDialogClarityEnable(SRSCshpObj cshpObj, SRSBool enable);
SRSResult			SRS_CSHP_SetDialogClarityLevel(SRSCshpObj cshpObj, SRSInt16 level); //I16.SRS_FOCUS_IWL (I16.1)

//Definition:
void				SRS_CSHP_SetDefinitionEnable(SRSCshpObj cshpObj, SRSBool enable);
SRSResult			SRS_CSHP_SetDefinitionLevel(SRSCshpObj cshpObj, SRSInt16 level); //I16.SRS_DEFINITION_IWL (I16.1)

//TruBass:
void				SRS_CSHP_SetTruBassEnable(SRSCshpObj cshpObj, SRSBool enable);
SRSResult			SRS_CSHP_SetTruBassLevel(SRSCshpObj cshpObj, SRSInt16 level);	//I16.SRS_TB_CTRL_IWL (I16.1)
SRSResult			SRS_CSHP_SetTruBassCompressorLevel(SRSCshpObj cshpObj, SRSInt16 level); //compressor control, 0~1.0, default 0.25, I16.SRS_SATB_CTRL_IWL
SRSResult			SRS_CSHP_SetTruBassSpeakerSize(SRSCshpObj cshpObj, SRSTBHDSpeakerSize sz);
SRSResult			SRS_CSHP_SetTruBassMode(SRSCshpObj cshpObj, SRSTBHDMode mode);
void				SRS_CSHP_SetTruBassSplitAnalysisEnable(SRSCshpObj cshpObj, SRSBool enable);				//disabled by default

//Limiter:
void				SRS_CSHP_SetLimiterEnable(SRSCshpObj cshpObj, SRSBool enable);
SRSResult			SRS_CSHP_SetLimiterMinimalGain(SRSCshpObj cshpObj, SRSInt32 value); //I32.2

//"Get" functions:
SRSBool				SRS_CSHP_GetEnable(SRSCshpObj cshpObj);
SRSInt16			SRS_CSHP_GetInputGain(SRSCshpObj cshpObj);	//max gain: <1
SRSInt16			SRS_CSHP_GetOutputGain(SRSCshpObj cshpObj);	//max gain: <1
SRSInt16			SRS_CSHP_GetBypassGain(SRSCshpObj cshpObj);	//max gain: <1
SRSCshpRenderingMode SRS_CSHP_GetRenderingMode(SRSCshpObj cshpObj);

//CSDecoder:
SRSCSDProcMode		SRS_CSHP_GetCSDecoderProcMode(SRSCshpObj cshpObj);

//Focus (DialogClarity):
SRSBool				SRS_CSHP_GetDialogClarityEnable(SRSCshpObj cshpObj);
SRSInt16			SRS_CSHP_GetDialogClarityLevel(SRSCshpObj cshpObj);

//Definition:
SRSBool				SRS_CSHP_GetDefinitionEnable(SRSCshpObj cshpObj);
SRSInt16			SRS_CSHP_GetDefinitionLevel(SRSCshpObj cshpObj);

//TruBass:
SRSBool				SRS_CSHP_GetTruBassEnable(SRSCshpObj cshpObj);
SRSInt16			SRS_CSHP_GetTruBassLevel(SRSCshpObj cshpObj);
SRSInt16			SRS_CSHP_GetTruBassCompressorLevel(SRSCshpObj cshpObj);
SRSTBHDSpeakerSize	SRS_CSHP_GetTruBassSpeakerSize(SRSCshpObj cshpObj);
SRSTBHDMode			SRS_CSHP_GetTruBassMode(SRSCshpObj cshpObj);
SRSTBHDCustomSpeakerCoefs	SRS_CSHP_GetTruBassCustomSpeakerFilterCoefs(SRSCshpObj cshpObj);
int					SRS_CSHP_GetTruBassSplitAnalysisEnable(SRSCshpObj cshpObj);

//Limiter:
SRSBool				SRS_CSHP_GetLimiterEnable(SRSCshpObj cshpObj);
SRSInt32			SRS_CSHP_GetLimiterMinimalGain(SRSCshpObj cshpObj);

//Version info get functions:
unsigned char SRS_CSHP_GetTechVersion(SRSVersion which);
unsigned char SRS_CSHP_GetLibVersion(SRSVersion which);

const SRSLibInfo*	SRS_CSHP_GetLibsInfo();

#ifdef __cplusplus
}
#endif /*__cplusplus*/


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#endif /*__SRS_CSHP_API_H__*/
