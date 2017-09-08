/*************************************************************************************
 * 
 * Description:
 *		Define ScaladoHdrLowlight to set scalado HDR & Lowlight.
 *
 * Author : wutangzhi
 * Email  : wutz@gionee.com
 * Date   : 2012-06-11
 *
 *************************************************************************************/

#include "ScaladoHdrLowlight.h"
#include "oslfile.h"
#include "oslmem.h"
#include "scbdefs.h"
#include "caps_base.h"
#include "ctstream_buffer.h"

namespace android {

ScaladoHdrLowlight::
ScaladoHdrLowlight() 
{
	mLowlight = NULL;
	mHDR = NULL;
	mImageCounter = 0;
}

void
ScaladoHdrLowlight::
deinit()
{
	if (mLowlight != NULL) {
		ctlowlight_destroy(mLowlight);	
		mLowlight = NULL;
	}

	if (mHDR != NULL) {
		cthdr2_destroy(mHDR);
		mHDR = NULL;
	}

	mImageCounter = 0;
}

CRESULT
ScaladoHdrLowlight::
setHDRBurstCnt(int count) 
{
	CRESULT res = CERR_OK;

	mHDRCount = count;

	return res;
}

CRESULT
ScaladoHdrLowlight::
setLowlightBurstCnt(int count) 
{
	CRESULT res = CERR_OK;

	mLowlightCount = count;

	return res;
}

CRESULT
ScaladoHdrLowlight::
addHDRImage(CTSession session, CTStream* outputStream, CTExifSession exif) 
{
	CRESULT res = CERR_OK;

	if (mHDR == NULL) {
		res = cthdr2_create(&mHDR);
		if (res != CERR_OK) {
			PRINTE_RES("Failed to create HDR", res);
			return res;
		}
	}

	if (mImageCounter >= mHDRCount) {
		mImageCounter = 0;
	} 

	if (mHDRCount == 3 && mImageCounter != HDR_NORMAL_IMAGE_INDEX) {
		res = cthdr2_addLDRSession(mHDR, session);
		if (res != CERR_OK) {
			PRINTE_RES("Failed to add source session for HDR", res);
		}
	} 
	
	if (++mImageCounter == mHDRCount) {
		res = renderHDRImage(outputStream, exif);
		if (res != CERR_OK) {
			handleError(session, outputStream, exif);
		}
	} 

	return res;
	
}

CRESULT
ScaladoHdrLowlight::
addLowlightImage(CTSession session, CTStream* outputStream, CTExifSession exif) 
{
	CRESULT res = CERR_OK;

	if (mLowlight == NULL) {
		res = ctlowlight_create(&mLowlight);
		if (res != CERR_OK) {
			PRINTE_RES("Failed to create lowlight", res);
			return res;
		}
	}

	if (mImageCounter >= LOWLIGHT_BURST_CNT) {
		mImageCounter = 0;
	} 

	res = ctlowlight_addSourceSession(mLowlight, session);
	if (res != CERR_OK) {
		PRINTE_RES("Failed to add source session for lowlight", res);
	} 
	
	mImageCounter ++;
	
	if (mImageCounter == LOWLIGHT_NORMAL_IMAGE_INDEX) {
		res = ctlowlight_addSourceSession(mLowlight, session);
		if (res != CERR_OK) {
			PRINTE_RES("Failed to add source session for lowlight", res);
		} 

		mImageCounter ++;
	}

	if (mImageCounter == LOWLIGHT_BURST_CNT) {
		res = renderLowlightImage(outputStream, exif);
		if (res != CERR_OK) {
			handleError(session, outputStream, exif);
		}
	}

	return res;
}

CRESULT
ScaladoHdrLowlight::
renderHDRImage(CTStream* outputStream, CTExifSession exif)
{
	CRESULT res = CERR_OK;
	CTImage* image = NULL;
	CTuint32 scanline = 0;
	CTSize size= {0, 0};
	CTSession session;
	
	res = cthdr2_getRenderSize(mHDR, &size);
	if (res != CERR_OK) {
		PRINTE_RES("Failed to get size", res);
		goto EXIT;
	}

	scanline = (caps_pixelBitSize(CM_YUV420P) * size.w) / 8;
	res = caps_createImage(0, size, scanline, CM_YUV420P, &image);
	if(res != CERR_OK) {
		PRINTE_RES("Failed to create image", res);
		goto EXIT;
	}

	res = cthdr2_renderToImage(mHDR, image);
	if (res != CERR_OK) {
		PRINTE_RES("Failed to render image", res);
		goto EXIT;
	}

	res = caps_newSessionWithRaw(image, &session);
	if (res != CERR_OK) {
		PRINTE_RES("Failed to create session", res);
		goto EXIT;
	}

	res = exif_addExifHeaderFromSession(session, exif);
	if (res != CERR_OK) {
		PRINTE_RES("Failed to add exif", res);
	}

	res = caps_render(session, outputStream, size, CAPS_OUTPUT_PRESERVE_AR, IMAGE_FORMAT_JPEG, 0);

	caps_destroySession(session);
	session = NULL;
		
EXIT:
	if (image != NULL) {
		caps_destroyImage(image);
		image = NULL;
	}

	if (mHDR != NULL) {
		cthdr2_destroy(mHDR);
		mHDR = NULL;
	}
	
	mImageCounter = 0;

	return res;
}

CRESULT
ScaladoHdrLowlight::
renderLowlightImage(CTStream* outputStream, CTExifSession exif)
{
	CRESULT res = CERR_OK;
	CTImage* image = NULL;
	CTuint32 scanline = 0;
	CTSize size= {0, 0};
	CTSession session;

	res = ctlowlight_getRenderSize(mLowlight, &size);
	if (res != CERR_OK) {
		PRINTE_RES("Failed to get size", res);
		goto EXIT;
	}

	scanline = (caps_pixelBitSize(CM_YUV420P) * size.w) / 8;
	res = caps_createImage(0, size, scanline, CM_YUV420P, &image);
	if(res != CERR_OK) {
		PRINTE_RES("Failed to create image", res);
		goto EXIT;
	}

	res = ctlowlight_renderToImage(mLowlight, image);
	if (res != CERR_OK) {
		PRINTE_RES("Failed to render image", res);
		goto EXIT;
	}

	res = caps_newSessionWithRaw(image, &session);
	if (res != CERR_OK) {
		PRINTE_RES("Failed to create session", res);
		goto EXIT;
	}

	res = exif_addExifHeaderFromSession(session, exif);
	if (res != CERR_OK) {
		PRINTE_RES("Failed to add exif", res);
	}

	res = caps_render(session, outputStream, size,CAPS_OUTPUT_PRESERVE_AR, IMAGE_FORMAT_JPEG, 0);
	
	caps_destroySession(session);
	session = NULL;
		
EXIT:
	if (image != NULL) {
		caps_destroyImage(image);
		image = NULL;
	}

	if (mLowlight != NULL) {
		ctlowlight_destroy(mLowlight);	
		mLowlight = NULL;
	}
	
	mImageCounter = 0;

	return res;
}

CRESULT 
ScaladoHdrLowlight::
handleError(CTSession session, CTStream* outputStream, CTExifSession exif)
{
	CRESULT res = CERR_OK;
	CTSize size = {0, 0};

	res = caps_getSourceImageSize(session, &size);
	if(res != CERR_OK) {
		PRINTE_RES("caps_getSourceImageSize fail", res);
		goto EXIT;
	}

	res = exif_addExifHeaderFromSession(session, exif);
	if (res != CERR_OK) {
		PRINTE_RES("Failed to add exif", res);	
	}

	res = caps_render(session, outputStream, size,
		CAPS_OUTPUT_PRESERVE_AR, IMAGE_FORMAT_JPEG, 0);

EXIT:
	return res;
}

} /* namespace android */
