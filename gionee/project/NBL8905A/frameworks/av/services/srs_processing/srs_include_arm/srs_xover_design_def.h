/********************************************************************************
 *	SRS Labs CONFIDENTIAL
 *	@Copyright 2011 by SRS Labs.
 *	All rights reserved.
 *
 *  Description:
 *  SRS audio crossover filters (Linkwitz¨CRiley crossover) design types, constants
 *
 *  Authour: Oscar Huang
 *
 *  RCS keywords:
 *	$Id$
 *  $Author$
 *  $Date$
 *	
********************************************************************************/
#ifndef __SRS_XOVER_DESIGN_DEF_H__
#define __SRS_XOVER_DESIGN_DEF_H__

#include "srs_iir_design_def.h"

//The order of xover filter must be even!
#define SRS_XOVER_FLOAT_COEFFICIENT_ARRAY_LEN(order)	SRS_IIR_FLOAT_COEFFICIENT_ARRAY_LEN(order)	//in float type elements
#define SRS_XOVER_FXP_COEFFICIENT_ARRAY_LEN(order)		SRS_IIR_FXP_COEFFICIENT_ARRAY_LEN(order)	//in SRSInt32, SRSInt24 or SRSInt16 elements

#define SRS_XOVER_DESIGN_WORKSPACE_SIZE(order)			((((order)/2)*5+1)*sizeof(float)*2+(5*((order)/2)+3*ANALYSIS_BLOCKSIZE)*sizeof(float)+8) //in bytes


#endif //__SRS_XOVER_DESIGN_DEF_H__
