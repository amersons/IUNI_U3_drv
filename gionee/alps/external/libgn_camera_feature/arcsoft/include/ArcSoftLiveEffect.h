/*************************************************************************************
 * 
 * Description:
 * 	Defines ArcSoft APIs for face beauty.
 *
 * Author : wutangzhi
 * Email  : wutz@gionee.com
 * Date   : 2013-09-07
 *
 *************************************************************************************/
 
#ifndef ANDROID_ARCSOFT_LIVE_EFFECT_H
#define ANDROID_ARCSOFT_LIVE_EFFECT_H

#include "amcomdef.h"
#include "amdisplay.h"
#include "merror.h"
#include "amipengine.h"

#include "GNCameraFeatureDefs.h"
#include "GNCameraFeatureListener.h"

namespace android { 
class ArcSoftLiveEffect {
public:
    ArcSoftLiveEffect();
	~ArcSoftLiveEffect();
	
	int32 init();
    void  deinit();
	int32 setLiveEffectType(GNLiveEffect_t type);
	int32 processLiveEffect(LPASVLOFFSCREEN param, bool isMirror);

private:
	int32 getEffectID(GNLiveEffect_t type);

private:
	int32 mEffectID;
};
};
#endif /* ANDROID_ARCSOFT_LIVE_EFFECT_H */
