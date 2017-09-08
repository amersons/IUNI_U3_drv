/********************************************************************************
 *	SRS Labs CONFIDENTIAL
 *	@Copyright 2010 by SRS Labs.
 *	All rights reserved.
 *
 *  Description:
 *  SRS audio crossover filters (Linkwitz¨CRiley crossover) filter design APIs
 *
 *  Authour: Oscar Huang
 *
 *  RCS keywords:
 *	$Id$
 *  $Author$
 *  $Date$
 *	
********************************************************************************/
#ifndef __SRS_XOVER_DESIGN_API_H__
#define __SRS_XOVER_DESIGN_API_H__

#include "srs_typedefs.h"
#include "srs_xover_design_def.h"

#ifdef __cplusplus
extern "C"{
#endif /*__cplusplus*/

//SRS' specific crossover filter design:

/*************************************************************************************************
 * Design floating point xover filters
 * Parameters:
 *		cutoff: [IN] The cutoff frequency
 *		order:	[IN] The order of the L-R filter
 *		sampleRate: [IN] The sampling rate
 *		lpfCoefs, hpfCoefs: [OUT] The designed LPF and HPF xover filter coefficients. The filter coefficients are
 *                    returned in the array in the following pattern respectively:

					//{
					//Band 0:
					//Coefficient B0
					//Coefficient B1
					//Coefficient B2
					//Coefficient A1
					//Coefficient A2
					               
					//Band 1:
					//Coefficient B0
					//Coefficient B1
					//Coefficient B2
					//Coefficient A1
					//Coefficient A2

					//...(more bands)
					      
					//Gain
					}
 
 * Return: SRS_STAT_NO_ERROR if design succeeds.Otherwise, an error code.

**************************************************************************************************/
SRSResult SRS_XoverFilterDesignFloat(float cutoff, int order, int sampleRate, float *lpfCoefs, float *hpfCoefs);

//SRS' specific crossover filter design:
/*************************************************************************************************
 * Design 32-bit/16-bit fixed point xover filters
 * Parameters:
 *		cutoff: [IN] The cutoff frequency
 *		order:	[IN] The order of the L-R filter
 *		sampleRate: [IN] The sampling rate
 *		lpfCoefs, hpfCoefs: [OUT] The designed LPF and HPF xover filter coefficients. The filter coefficients are
 *                    returned in the array in the following pattern respectively:


					//{
					//Band 0:
					//iwl
					//Coefficient B0
					//Coefficient B1
					//Coefficient B2
					//Coefficient A1
					//Coefficient A2
					               
					//Band 1:
					//iwl
					//Coefficient B0
					//Coefficient B1
					//Coefficient B2
					//Coefficient A1
					//Coefficient A2

					//...(more bands)
					    
					//Gain iwl    
					//Gain
					}
		ws:	[IN] workspace scratch memory, whose size must be at least SRS_XOVER_DESIGN_WORKSPACE_SIZE(order)
 
 * Return: SRS_STAT_NO_ERROR if design succeeds.Otherwise, an error code.

**************************************************************************************************/
SRSResult SRS_XoverFilterDesignFxp16(float cutoff, int order, int sampleRate, SRSInt16 *lpfCoefs, SRSInt16 *hpfCoefs, void *ws);
SRSResult SRS_XoverFilterDesignFxp24(float cutoff, int order, int sampleRate, SRSInt24 *lpfCoefs, SRSInt24 *hpfCoefs, void *ws);
SRSResult SRS_XoverFilterDesignFxp32(float cutoff, int order, int sampleRate, SRSInt32 *lpfCoefs, SRSInt32 *hpfCoefs, void *ws);


//Linkwitz-Riley crossover filter design below:
/*************************************************************************************************
 * Design floating point xover filters
 * Parameters:
 *		cutoff: [IN] The cutoff frequency
 *		order:	[IN] The order of the L-R filter
 *		sampleRate: [IN] The sampling rate
 *		lpfCoefs, hpfCoefs: [OUT] The designed LPF and HPF xover filter coefficients. The filter coefficients are
 *                    returned in the array in the following pattern respectively:

					//{
					//Band 0:
					//Coefficient B0
					//Coefficient B1
					//Coefficient B2
					//Coefficient A1
					//Coefficient A2
					               
					//Band 1:
					//Coefficient B0
					//Coefficient B1
					//Coefficient B2
					//Coefficient A1
					//Coefficient A2

					//...(more bands)
					      
					//Gain
					}
 
 * Return: SRS_STAT_NO_ERROR if design succeeds.Otherwise, an error code.

**************************************************************************************************/
SRSResult SRS_LinkwitzRileyDesignFloat(float cutoff, int order, int sampleRate, float *lpfCoefs, float *hpfCoefs);


/*************************************************************************************************
 * Design 32-bit/16-bit fixed point xover filters
 * Parameters:
 *		cutoff: [IN] The cutoff frequency
 *		order:	[IN] The order of the L-R filter
 *		sampleRate: [IN] The sampling rate
 *		lpfCoefs, hpfCoefs: [OUT] The designed LPF and HPF xover filter coefficients. The filter coefficients are
 *                    returned in the array in the following pattern respectively:


					//{
					//Band 0:
					//iwl
					//Coefficient B0
					//Coefficient B1
					//Coefficient B2
					//Coefficient A1
					//Coefficient A2
					               
					//Band 1:
					//iwl
					//Coefficient B0
					//Coefficient B1
					//Coefficient B2
					//Coefficient A1
					//Coefficient A2

					//...(more bands)
					    
					//Gain iwl    
					//Gain
					}
		ws:	[IN] workspace scratch memory, whose size must be at least SRS_XOVER_DESIGN_WORKSPACE_SIZE(order)
 
 * Return: SRS_STAT_NO_ERROR if design succeeds.Otherwise, an error code.

**************************************************************************************************/
SRSResult SRS_LinkwitzRileyDesignFxp16(float cutoff, int order, int sampleRate, SRSInt16 *lpfCoefs, SRSInt16 *hpfCoefs, void *ws);
SRSResult SRS_LinkwitzRileyDesignFxp32(float cutoff, int order, int sampleRate, SRSInt32 *lpfCoefs, SRSInt32 *hpfCoefs, void *ws);

#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif //__SRS_XOVER_DESIGN_API_H__
