/*******************************************************************************
 *
 * Description: 
 *		Define ScaladoPictureFrame to set picture frame.
 *
 * Author  : wutangzhi
 * Email   : wutz@gionee.com
 * Date    : 2012-06-11
 *
 *******************************************************************************/

#include <string.h>

#include "ScaladoPictureFrame.h"

namespace android {

ScaladoPictureFrame::
ScaladoPictureFrame() 
{

}

CRESULT 
ScaladoPictureFrame::
renderPictureFrameImage(CTSession session, CTchar* frameName, GNCameraType_t cameraType, int orientation)
{
	CRESULT res = CERR_OK;
	CTBuffer* frameBuffer = NULL;
	CTSession rawSession = NULL;
	CTImage* image = NULL;
	CTSize size;
	CTchar fileName[256] = {0};
	int scanline = 0;
	CTBuffer* buffer = NULL;

	if (frameName == NULL && session == NULL) {
		return res;
	}
	
	sprintf(fileName, "%s/%s.9.png", PICTURE_FRAME_PATH, frameName);

	res = caps_newSessionWithFile(fileName, IMAGE_FORMAT_PNG, &rawSession);
	if (res != CERR_OK) {
		PRINTE_RES("Failed to new session", res);
		goto EXIT;
	}

	res = caps_getSourceImageSize(rawSession, &size);
	if(res != CERR_OK) {
		PRINTE_RES("caps_getSourceImageSize fail", res);
		goto EXIT;
	}

	if (orientation == 90 || orientation == 270) {
		size.h = size.h + size.w;
		size.w = size.h - size.w;
		size.h = size.h - size.w;
	}
	
	scanline = (caps_pixelBitSize(CM_RGBA8888) * size.w + 7) / 8;
	res = caps_createBuffer(size.h * scanline, &buffer);
	if(res != CERR_OK) {
		PRINTE_RES("caps_createBuffer fail", res);
		goto EXIT;
	}

	res = caps_createImage(buffer, size, scanline, CM_RGBA8888, &image);
	if(res != CERR_OK) {
		PRINTE_RES("caps_createImage fail", res);
		goto EXIT;
	}

	if (orientation == 90 || orientation == 270) {
		res = caps_beginRotate(rawSession);
		if (res == CERR_OK) {
			res = caps_setRotate(rawSession, ROTATE_TO_90);
			if (res != CERR_OK) {
				PRINTE("Failed to set rotation effect");
			}

			caps_endRotate(rawSession);
		}
	}

	if (cameraType == GN_CAMERA_TYPE_FRONT) {
		res = caps_beginFlip(rawSession);
		if (res == CERR_OK) {
			res = caps_setFlip(rawSession, FLIP_HORIZONTAL);

			if (res != CERR_OK) {
				PRINTE("Failed to set flip effect");
			}

			caps_endFlip(rawSession);
		}
	}

	res = caps_renderAsRawToBuffer(rawSession, image, CAPS_OUTPUT_PRESERVE_AR, 0);
	if(res != CERR_OK) {
		PRINTE_RES("caps_renderAsRawToBuffer fail", res);
		goto EXIT;
	}

	res = caps_insertFrameFromRaw(session, image, OWNERSHIP_CAPS);
	if (res != CERR_OK) {
		PRINTE_RES("Failed to render picture frame", res);
	}

EXIT:
	if (rawSession != NULL) {
		caps_destroySession(rawSession);
	}

	return res;
}

void 
ScaladoPictureFrame::
deinit() 
{

}

};


