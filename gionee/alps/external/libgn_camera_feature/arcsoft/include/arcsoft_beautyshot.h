#ifndef __ARC_BEAUTY_SHOT_H__
#define __ARC_BEAUTY_SHOT_H__

#include "amcomdef.h"
#include "asvloffscreen.h"

#ifdef __cplusplus
extern "C" {
#endif


#define AFF_MAX_FACE_NUM			8
typedef struct{
	MLong 	    AgeResultArray[AFF_MAX_FACE_NUM];	/*The age result array ; 
											         0 means unknown, and valid age is bigger than 0*/
	MLong 	    GenderResultArray[AFF_MAX_FACE_NUM];/*The gender result array ; 
											          1 means female ,0 means male, and -1 means unknown*/
	MRECT       FaceRect[AFF_MAX_FACE_NUM];		/* Face Rect */
	MLong		lFaceNumber;		/* Face Number */
}AFF_AGEGENDERRESULT;

typedef struct {
	//previous processing parameter
	MLong 		lSlenderFaceLevel;
	MLong 		lSkinSoftenLevel;
	MLong 		lEyeEnlargmentLevel;

	//post processing
	MLong 		lSkinBrightLevel;
	MLong 		lEyeBrightLevel;
	MLong 		lAntiShineLevel;
	MLong 		lTeethWhiteLevel;		
}BEAUTY_PARAM;

typedef struct{
	BEAUTY_PARAM   AgeGenderParam[AFF_MAX_FACE_NUM];	/*The age and Gender param array ;*/ 
	MLong		lFaceNumber;		/* Face Number in AFF_AGEGENDERRESULT */

}AFF_AGEGENDER_PARAM;


// only support previous processing parameters
MRESULT BS_Init(int nWidthPreview, int nHeightPreview);//preview resolution
MRESULT BS_GetPreviewAgeGenderResult(LPASVLOFFSCREEN pImgSrc, AFF_AGEGENDERRESULT* pAgeGenderRes);
MRESULT BS_ProcessPreview(LPASVLOFFSCREEN pImgSrc);
MRESULT BS_ProcessPreviewEx(LPASVLOFFSCREEN pImgSrc, AFF_AGEGENDER_PARAM agegenderParam);
MRESULT BS_SetParameter(BEAUTY_PARAM* pParam);
void	BS_Uninit();

//support all parameters
MRESULT BS_GetImageAgeGenderResult(LPASVLOFFSCREEN pImgSrc, AFF_AGEGENDERRESULT* pAgeGenderRes);
MRESULT BS_ProcessImage(LPASVLOFFSCREEN pImgSrc,BEAUTY_PARAM* pParam);
MRESULT BS_ProcessImageEx(LPASVLOFFSCREEN pImgSrc,AFF_AGEGENDER_PARAM agegenderParam);

#ifdef __cplusplus
}
#endif

#endif //__ARC_BEAUTY_SHOT_H__
