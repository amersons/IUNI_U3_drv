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
#ifndef SCALADO_HDR_LOWLIGHT_H
#define SCALADO_HDR_LOWLIGHT_H

#include "stdio.h"
#include "scbdefs.h"
#include "caps_base.h"
#include "fm_hdr2.h"
#include "fm_lowlight.h"
#include "fm_exif.h"
#include "ScaladoCameraFeatureDefs.h"

namespace android {

class ScaladoHdrLowlight {
public:
	ScaladoHdrLowlight();

	void  deinit();
	CRESULT	setHDRBurstCnt(int count);
	CRESULT addHDRImage(CTSession session, CTStream* outputStream, CTExifSession exif);
	CRESULT setLowlightBurstCnt(int count);
	CRESULT addLowlightImage(CTSession session, CTStream* outputStream, CTExifSession exif);

private:
	CRESULT renderHDRImage(CTStream* outputStream, CTExifSession exif);
	CRESULT renderLowlightImage(CTStream* outputStream, CTExifSession exif);
	CRESULT handleError(CTSession session, CTStream* outputStream, CTExifSession exif);
	
	CTLowLight* mLowlight;
	CTHDR2* mHDR;
	int mImageCounter;
	int mHDRCount;
	int mLowlightCount;
};

} /* namespace android */

#endif /* SCALADO_HDR_LOWLIGHT_H */