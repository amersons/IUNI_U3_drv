/*******************************************************************************
 *
 * Description: 
 *		Define ScaladoLiveEffect to set scalado live effects.
 *
 * Author  : wutangzhi
 * Email   : wutz@gionee.com
 * Date    : 2012-06-11
 *
 *******************************************************************************/

#ifndef SCALADO_CAMERA_LIVE_EFFECT_H
#define SCALADO_CAMERA_LIVE_EFFECT_H

#include "stdio.h"
#include "scbdefs.h"
#include "caps_base.h"
#include "fm_photoart.h"
#include "ScaladoCameraFeatureDefs.h"

#include <GNCameraFeatureDefs.h>

namespace android {

class ScaladoLiveEffect{
public:
	ScaladoLiveEffect();
   	CRESULT setScaladoLiveEffect(CTSession session, GNLiveEffect_t effect, 
										int width, int height);

private:
	CRESULT setAntiqueEffect(CTSession session);
   	CRESULT setCartoonEffect(CTSession session);
	CRESULT setEmbossEffect(CTSession session);
	CRESULT setFlipEffect(CTSession session);
	CRESULT setFogEffect(CTSession session);
	CRESULT setGrayscaleEffect(CTSession session);
	CRESULT setLomoEffect(CTSession session, CAPS_LOMO_STYLE lomoStyle);
	CRESULT setMagicpenEffect(CTSession session);
	CRESULT setMilkyEffect(CTSession session);
	CRESULT setMirrorEffect(CTSession session);
	CRESULT setNegativeEffect(CTSession session);
	CRESULT setOilyEffect(CTSession session);
	CRESULT setPaintEffect(CTSession session);
	CRESULT setSepiaEffect(CTSession session);
	CRESULT setSketchEffect(CTSession session, CAPS_SKETCH_MODE mode);
	CRESULT setSolarizeEffect(CTSession session);
	CRESULT setStampEffect(CTSession session);
	CRESULT setDofEffect(CTSession session); //FIXME
	CRESULT setVignettingEffect(CTSession session);
	CRESULT setWarpEffect(CTSession session, const DCHAR* filename, int index);
	CRESULT setMosaicEffect(CTSession session);
	CRESULT setForstEffect(CTSession session);
	CRESULT setMoonLightEffect(CTSession session);
	CRESULT setNoiseEffect(CTSession session);
	CRESULT setWaterColorEffect(CTSession session);

	int mWidth;
	int mHeight;
};

};
#endif /* SCALADO_CAMERA_LIVE_EFFECT_H */


