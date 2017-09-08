#ifndef __ARC_VSIGN_H__
#define __ARC_VSIGN_H__

#include "amcomdef.h"
#include "asvloffscreen.h"

#ifdef __cplusplus
extern "C" {
#endif

MRESULT VS_Init(int nWidthPreview, int nHeightPreview);//preview resolution
MRESULT VS_ProcessPreview(LPASVLOFFSCREEN pImgSrc,PMRECT pRect);
MVoid	 VS_Uninit();

#ifdef __cplusplus
}
#endif

#endif //__ARC_VSIGN_H__