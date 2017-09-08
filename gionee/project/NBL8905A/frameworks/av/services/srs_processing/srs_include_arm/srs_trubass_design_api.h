/********************************************************************************
 *	SRS Labs CONFIDENTIAL
 *	@Copyright 2010 by SRS Labs.
 *	All rights reserved.
 *
 *  Description:
 *  SRS TruBass filter design APIs
 *
 *  Authour: Oscar Huang
 *
 *  RCS keywords:
 *	$Id: //srstech/srs_designer/std_fxp/include/srs_trubass_design_api.h#2 $
 *  $Author: oscarh $
 *  $Date: 2011/01/12 $
 *	
********************************************************************************/
#ifndef __SRS_TRUBASS_DESIGN_API_H__
#define __SRS_TRUBASS_DESIGN_API_H__

#include "srs_trubass_design_def.h"
#include "srs_typedefs.h"

#ifdef __cplusplus
extern "C"{
#endif /*__cplusplus*/

/******************************************************************************************
 * Design floating point speaker filters for Trubass
 * Parameters:
 *	lowFreq: [IN] low pass filter cut off of the speaker filter
 *  samplingRate: [IN] the sampling rate
 *  coefs: [OUT] the designed filter coefficients. Filter coefficients are arranged in
 *				  the following pattern:
	struct
	{
		float	LowPassAudioFilterCoef[2]; //b0, a1
		float	LowBandAudioFilterCoef[3]; //b0, a1, a2
		float	MidBandAudioFilterCoef[3]; //b0, a1, a2
	}
 *
*******************************************************************************************/
//void SRS_TruBassFilterDesignFloat(float lowFreq, float samplingRate, float *coefs);

/******************************************************************************************
 * Design floating point speaker filters for Split-Analysis Trubass
 * Parameters:
 *	lowFreqAudio: [IN] low pass filter cut off of the audio filter
 *  lowFreqAnalysis: [IN] low pass filter cut off of the analysis filter
 *  samplingRate: [IN] the sampling rate
 *  speakerCoefs: [OUT] the designed filter coefficients. Filter coefficients are arranged in
 *				  the following pattern:
	union
	{
		struct
		{
			float	LowPassAudioFilterCoef[2]; //b0, a1
			float	LowBandAudioFilterCoef[3]; //b0, a1, a2
			float	MidBandAudioFilterCoef[3]; //b0, a1, a2
			float	LowPassAnalysisFilterCoef[2];
			float	LowBandAnalysisFilterCoef[3];
			float	MidBandAnalysisFilterCoef[3];
		} Struct;
		float	Array[16];
	} 
*******************************************************************************************/
void SRS_TruBassHDFilterDesignFloat(float lowFreqAudio, float lowFreqAnalysis, int sampleRate, float *speakerCoefs);


/******************************************************************************************
 * Design fixed-point speaker filters for TruBass. The returned coefficient structure can
 * be used with the SRS_SetTruBassCustomSpeakerFilterCoefs API of srs_trubass
 * Parameters:
  *  lowFreq: [IN]low pass filter cut off of the speaker filter
  *  samplingRate: [IN] the sampling rate
  *  ws:  [IN] workspace, whose size must be at least SRS_TRUBASS_DESIGN_WORKSPACE_SIZE bytes
* Return:
  * The designed fixed-point coefficient structure
*******************************************************************************************/
//SRSTruBassCustomSpeakerCoefs SRS_TruBassFilterDesignFxp(float lowFreq, float samplingRate, void *ws);


/******************************************************************************************
 * Design 32-bit fixed-point speaker filters for Split-Analysis TruBass
 * Parameters:
 *	lowFreqAudio: [IN] low pass filter cut off of the audio filter
 *  lowFreqAnalysis: [IN] low pass filter cut off of the analysis filter
 *  samplingRate: [IN] the sampling rate
 *  speakerCoefs: [OUT] the designed filter coefficients. Filter coefficients are arranged in
 *				  the following pattern:
	union
	{
		struct
		{
			SRSInt32	LowPassAudioFilterCoef[2];
			SRSInt32	LowBandAudioFilterCoef[3];
			SRSInt32	MidBandAudioFilterCoef[3];
			SRSInt32	LowPassAnalysisFilterCoef[2];
			SRSInt32	LowBandAnalysisFilterCoef[3];
			SRSInt32	MidBandAnalysisFilterCoef[3];
		} Struct;
		SRSInt32	Array[16];
	} 
 *  ws:  [IN] workspace, whose size must be at least SRS_TBHD_DESIGN_WORKSPACE_SIZE bytes
*******************************************************************************************/
void SRS_TruBassHDFilterDesignFxp32(float lowFreqAudio, float lowFreqAnalysis, int sampleRate, SRSInt32 *speakerCoefs, void *ws);
void SRS_TruBassHDFilterDesignFxp24(float lowFreqAudio, float lowFreqAnalysis, int sampleRate, SRSInt24 *speakerCoefs, void *ws);

#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif //__SRS_TRUBASS_DESIGN_API_H__
