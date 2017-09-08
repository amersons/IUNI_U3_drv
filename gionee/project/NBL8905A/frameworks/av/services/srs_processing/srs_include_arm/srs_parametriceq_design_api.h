/********************************************************************************
 *	SRS Labs CONFIDENTIAL
 *	@Copyright 2010 by SRS Labs.
 *	All rights reserved.
 *
 *  Description:
 *  SRS ParametricEQ filter design APIs
 *
 *  Authour: Oscar Huang
 *
 *  RCS keywords:
 *	$Id: //srstech/srs_designer/std_fxp/include/srs_parametriceq_design_api.h#1 $
 *  $Author: oscarh $
 *  $Date: 2010/09/26 $
 *	
********************************************************************************/
#ifndef __SRS_PARAMETRICEQ_DESIGN_API_H__
#define __SRS_PARAMETRICEQ_DESIGN_API_H__

#include "srs_parametriceq_design_def.h"
#include "srs_typedefs.h"

#ifdef __cplusplus
extern "C"{
#endif /*__cplusplus*/

/*************************************************************************************************
 * Design floating point PEQ filters
 * Parameters:
 *		peqSpec: [IN] PEQ specification: sampling rate, the number of bands, bands specs
 *		coefs:	[OUT] The designed filter coefficients. The length of the coefficient array is
 *                    SRS_PEQ_FLOAT_COEFFICIENT_ARRAY_LEN(NumOfBands). The filter coefficients are
 *                    returned in the array in the following pattern:

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
SRSResult SRS_ParametriceqDesignFloat(SRSParametriceqSpec *peqSpec, float *coefs);

/*************************************************************************************************
 * Design 32-bit fixed point PEQ filters
 * Parameters:
 *		peqSpec: [IN] PEQ specification: sampling rate, the number of bands, bands specs
 *		coefs:	[OUT] The designed filter coefficients. The length of the coefficient array is
 *                    SRS_PEQ_FLOAT_COEFFICIENT_ARRAY_LEN(NumOfBands). The filter coefficients are
 *                    returned in the array in the following pattern:

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
		ws:	[IN] workspace scratch memory, whose size must be at least SRS_PEQ_DESIGN_WORKSPACE_SIZE(NumOfBands)
 
 * Return: SRS_STAT_NO_ERROR if design succeeds.Otherwise, an error code.

**************************************************************************************************/
SRSResult SRS_ParametriceqDesignFxp16(SRSParametriceqSpec *peqSpec, SRSInt16 *coefs, void *ws);
SRSResult SRS_ParametriceqDesignFxp24(SRSParametriceqSpec *peqSpec, SRSInt24 *coefs, void *ws);
SRSResult SRS_ParametriceqDesignFxp32(SRSParametriceqSpec *peqSpec, SRSInt32 *coefs, void *ws);

#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif //__SRS_PARAMETRICEQ_DESIGN_API_H__
