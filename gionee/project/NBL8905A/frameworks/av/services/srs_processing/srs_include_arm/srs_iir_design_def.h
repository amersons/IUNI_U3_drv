/********************************************************************************
 *	SRS Labs CONFIDENTIAL
 *	@Copyright 2010 by SRS Labs.
 *	All rights reserved.
 *
 *  Description:
 *  SRS IIR filter design types, constants
 *
 *  Authour: Zesen Zhuang
 *
 *  RCS keywords:
 *	$Id$
 *  $Author$
 *  $Date$
 *	
********************************************************************************/
#ifndef __SRS_IIR_DESIGN_DEF_H__
#define __SRS_IIR_DESIGN_DEF_H__

#include "srs_filter_design_def.h"

typedef enum
{
	SRS_IIR_DESIGN_LP,
	SRS_IIR_DESIGN_HP
} SRSIirDesignType;

#define SRS_IIR_FLOAT_COEFFICIENT_ARRAY_LEN(order)		(5*(((order)+1)/2)+1)	//in float type elements
#define SRS_IIR_FXP_COEFFICIENT_ARRAY_LEN(order)		(6*(((order)+1)/2)+2)	//in SRSInt32 or SRSInt16 elements

#define SRS_IIR_DESIGN_WORKSPACE_SIZE(order)	(((((order)+1)/2)*5+1)*sizeof(float)+(5*(((order)+1)/2)+3*ANALYSIS_BLOCKSIZE)*sizeof(float)+8) //in bytes


#endif //__SRS_IIR_DESIGN_DEF_H__

