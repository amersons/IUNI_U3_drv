/*******************************************************************************
Copyright(c) ArcSoft, All right reserved.

This file is ArcSoft's property. It contains ArcSoft's trade secret, proprietary 
and confidential information. 

The information and code contained in this file is only for authorized ArcSoft 
employees to design, create, modify, or review.

DO NOT DISTRIBUTE, DO NOT DUPLICATE OR TRANSMIT IN ANY FORM WITHOUT PROPER 
AUTHORIZATION.

If you are not an intended recipient of this file, you must not copy, 
distribute, modify, or take any action in reliance on it. 

If you have received this file in error, please immediately notify ArcSoft and 
permanently delete the original and any copy of any file and any printout 
thereof.
*******************************************************************************/
#ifndef _ARCSOFT_PICZOOM_H_
#define _ARCSOFT_PICZOOM_H_

#include "asvloffscreen.h"
#include "merror.h"

#ifdef PICZOOMDLL_EXPORTS
#define PICZOOM_API __declspec(dllexport)
#else
#define PICZOOM_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
* This function is implemented by the caller, registered with 
* any time-consuming processing functions, and will be called 
* periodically during processing so the caller application can 
* obtain the operation status (i.e., to draw a progress bar), 
* as well as determine whether the operation should be canceled or not
************************************************************************/
typedef MRESULT (*ADZ_FNPROGRESS) (
	MLong		lProgress,				// The percentage of the current operation
	MLong		lStatus,				// The current status at the moment
	MVoid		*pParam					// Caller-defined data
);

/************************************************************************
* This function is used to get version information of library
************************************************************************/
typedef struct _tag_ADZ_Version {
	MLong		lCodebase;	/* Codebase version number */
	MLong		lMajor;		/* Major version number */
	MLong		lMinor;		/* Minor version number */
	MLong		lBuild;		/* Build version number, increasable only */
	const MChar *Version;	/* Version in string form */
	const MChar *BuildDate;	/* Latest build date */
	const MChar *CopyRight;	/* Copyrights */
} ADZ_Version;

PICZOOM_API MVoid ADZ_GetVersion(ADZ_Version *pVer);

/************************************************************************
* This function is used to get default parameters of library
************************************************************************/
#define ADZ_PROCESS_TYPE_IMAGE	0x1
#define ADZ_PROCESS_TYPE_VIDEO	0x2

typedef struct _tag_ADZ_CAPTURE_INFO {
	MLong				lBrightLevel;
	MLong				lBlackLevel;
	MFloat				fGains[4];
	MFloat				fColorCorrectMat[9];
	MFloat				*pfToneMapCurve;
	MLong				lCurveSize;
} ADZ_CAPTURE_INFO;

typedef struct _tag_ADZ_PARAM {
	MLong				lRefNum;
	MLong				lIntensity;
	MLong				lProcessType;
	MRECT				rtScaleRegion;
	ADZ_CAPTURE_INFO	*pCapInfo;
} ADZ_PARAM, *LPADZ_PARAM;

PICZOOM_API MRESULT ADZ_GetDefaultParam(LPADZ_PARAM pParam);

/************************************************************************
* The functions is used to perform image night shot
************************************************************************/
#define MAX_DZ_INPUT_IMAGES		8//12
typedef struct _tag_ADZ_INPUTINFO {
	MBool				bDualCam;
	MLong				lImgNum;
	LPASVLOFFSCREEN		pImages[MAX_DZ_INPUT_IMAGES];
} ADZ_INPUTINFO, *LPADZ_INPUTINFO;

PICZOOM_API MRESULT ADZ_Init(			    // return MOK if success, otherwise fail
	MVoid				*pMemBuf,			// [in]  The buffer of memory for algorithm
	MLong				lMemSize,			// [in]  The size of the memory buffer
	MHandle				*phEnhancer			// [out] The algorithm engine will be initialized by this API
);

PICZOOM_API MRESULT ADZ_Uninit(			    // return MOK if success, otherwise fail
	MHandle				*phEnhancer			// [in/out] The algorithm engine will be un-initialized by this API
);

PICZOOM_API MRESULT ADZ_Enhancement(	    // return MOK if success, otherwise fail
	MHandle				hEnhancer,			// [in]  The algorithm engine
	LPADZ_INPUTINFO		pSrcImgs,			// [in]  The offscreen of source images
	LPASVLOFFSCREEN		pDstImg,			// [out] The offscreen of result image
	LPADZ_PARAM			pDZParam,			// [in]  The parameters for algorithm engine	
	ADZ_FNPROGRESS		fnCallback,			// [in]  The callback function 
	MVoid				*pParam				// [in]  Caller-specific data that will be passed into the callback function
);

#ifdef __cplusplus
}
#endif

#endif // _ARCSOFT_PICZOOM_H_
