/********************************************************************************
 *	SRS Labs CONFIDENTIAL
 *	@Copyright 2010 by SRS Labs.
 *	All rights reserved.
 *
 *  Description:
 *  SRS ParametricEQ filter design types, constants
 *
 *  Authour: Oscar Huang
 *
 *  RCS keywords:
 *	$Id: //srstech/srs_designer/std_fxp/include/srs_parametriceq_design_def.h#1 $
 *  $Author: oscarh $
 *  $Date: 2010/09/26 $
 *	
********************************************************************************/
#ifndef __SRS_PARAMETRICEQ_DESIGN_DEF_H__
#define __SRS_PARAMETRICEQ_DESIGN_DEF_H__

#include "srs_filter_design_def.h"

typedef enum
{
	SRS_PEQ_BAND_TYPE_TRADITIONAL,
	SRS_PEQ_BAND_TYPE_LOWSHELF,
	SRS_PEQ_BAND_TYPE_HIGHSHELF,
	SRS_PEQ_BAND_TYPE_LOWPASS,
	SRS_PEQ_BAND_TYPE_HIGHPASS,
	SRS_PEQ_BAND_TYPE_BANDPASS,
	SRS_PEQ_BAND_TYPE_ALLPASS,
	SRS_PEQ_BAND_TYPE_NOTCH,
	SRS_PEQ_BAND_TYPE_PEAKING,
	SRS_PEQ_BAND_TYPE_NULL,
	SRS_PEQ_BAND_TYPE_NUM
} SRSParametriceqBandType;

typedef struct
{
	SRSParametriceqBandType		Type;
	float						CenterFreq;		//in Hz, physical frequency
	float						QFactor;		//ratio of band width/CenterFreq
	float						Gain;			//gain of the band in dB
	int							InvertPhase;	//Invert phase if nonzero
} SRSParametriceqBandSpec;


typedef struct
{
	int						NumOfBands;		//The number of bands
	SRSParametriceqBandSpec *BandSpecs;		//Specification array of all bands
	int						SampleRate;	//Sampling rate in Hz
} SRSParametriceqSpec;

#define SRS_PEQ_FLOAT_COEFFICIENT_ARRAY_LEN(nBands)		(5*(nBands)+1)	//in float type elements
#define SRS_PEQ_FXP_COEFFICIENT_ARRAY_LEN(nBands)		(6*(nBands)+2)	//in SRSInt32 type elements
#define SRS_PEQ_DESIGN_WORKSPACE_SIZE(nBands)	(((nBands)*5+1)*sizeof(float)+(5*(nBands)+3*ANALYSIS_BLOCKSIZE)*sizeof(float)+8) //in bytes


#endif //__SRS_PARAMETRICEQ_DESIGN_DEF_H__

