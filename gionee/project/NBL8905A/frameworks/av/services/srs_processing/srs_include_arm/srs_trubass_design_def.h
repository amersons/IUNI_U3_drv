/********************************************************************************
 *	SRS Labs CONFIDENTIAL
 *	@Copyright 2010 by SRS Labs.
 *	All rights reserved.
 *
 *  Description:
 *  SRS Trubass filter design types, constants
 *
 *  Authour: Oscar Huang
 *
 *  RCS keywords:
 *	$Id: //srstech/srs_designer/std_fxp/include/srs_trubass_design_def.h#2 $
 *  $Author: oscarh $
 *  $Date: 2011/01/12 $
 *	
********************************************************************************/
#ifndef __SRS_TRUBASS_DESIGN_DEF_H__
#define __SRS_TRUBASS_DESIGN_DEF_H__

#include "srs_parametriceq_design_def.h"

#define SRS_TBHD_FLOAT_COEFFICIENT_ARRAY_LEN	22		//in elements
#define SRS_TBHD_FXP_COEFFICIENT_ARRAY_LEN		24		//in elements

#define SRS_TBHD_DESIGN_WORKSPACE_SIZE	SRS_MAX((sizeof(float)*SRS_TBHD_FLOAT_COEFFICIENT_ARRAY_LEN+8), SRS_PEQ_DESIGN_WORKSPACE_SIZE(1))	//in bytes

#ifndef SRS_MAX
	#define SRS_MAX(a, b)  ((a)>=(b)?(a):(b))
#endif


#endif //__SRS_TRUBASS_DESIGN_DEF_H__
