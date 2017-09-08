/********************************************************************************
 *	SRS Labs CONFIDENTIAL
 *	@Copyright 2010 by SRS Labs.
 *	All rights reserved.
 *
 *  Description:
 *  Header file for the version get functions for srs_designer
 *
 *	Author: Oscar Huang
 *	
 *	(RCS keywords below, do not edit)
 *  $Id: //srstech/srs_designer/std_fxp/include/srs_designer_ver_api.h#1 $
 *  $Author: oscarh $
 *  $Date: 2010/11/16 $
********************************************************************************/
#ifndef __SRS_DESIGNER_VER_H__
#define __SRS_DESIGNER_VER_H__

#include "srs_typedefs.h"

#ifdef __cplusplus
extern "C"{
#endif /*__cplusplus*/

unsigned char SRS_Designer_GetLibVersion(SRSVersion which);
unsigned char SRS_Designer_GetTechVersion(SRSVersion which);

#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif //__SRS_DESIGNER_VER_H__

