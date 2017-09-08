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
 
#ifndef ANDROID_ARCSOFT_GESTUER_SHOT_H
#define ANDROID_ARCSOFT_GESTUER_SHOT_H

#include "arcsoft_victorysign.h"
#include "asvloffscreen.h"
#include "ammem.h"
#include "merror.h"

#include "GNCameraFeatureDefs.h"
#include "GNCameraFeatureListener.h"


namespace android { 
class ArcSoftGestureShot {
public:
    ArcSoftGestureShot();
	~ArcSoftGestureShot();
	
	int32 init();
    void  deinit();
	int32 setCameraListener(GNCameraFeatureListener* listener);
	int32 processGestureShot(LPASVLOFFSCREEN param);
	int32 enableGestureShot(int width, int height);
	int32 disableGestureShot();

private:
	GNCameraFeatureListener* mListener;
	bool mInitialized;
};
};
#endif /* ANDROID_ARCSOFT_GESTUER_SHOT_H */
