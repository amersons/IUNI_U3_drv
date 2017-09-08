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

#ifndef SCALADO_CAMERA_PICTURE_FRAME_H
#define SCALADO_CAMERA_PICTURE_FRAME_H

#include "stdio.h"
#include "scbdefs.h"
#include "caps_base.h"
#include "fm_photoart.h"
#include "ScaladoCameraFeatureDefs.h"

#include <GNCameraFeatureDefs.h>

namespace android {

class ScaladoPictureFrame{
public:
	ScaladoPictureFrame();
   	CRESULT renderPictureFrameImage(CTSession session, CTchar* frameName, 
		GNCameraType_t cameraType, int orientation);
	void deinit();
};

};
#endif /* SCALADO_CAMERA_PICTURE_FRAME_H */


