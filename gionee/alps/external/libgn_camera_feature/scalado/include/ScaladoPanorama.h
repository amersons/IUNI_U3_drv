/*******************************************************************************
 *
 * Description: 
 *		Define ScaladoPanorama to deal with panorama.
 *
 * Author  : wutangzhi
 * Email   : wutz@gionee.com
 * Date    : 2012-08-11
 *
 *******************************************************************************/

#ifndef SCALADO_CAMERA_PRANORAMA_H
#define SCALADO_CAMERA_PRANORAMA_H

#include <stdio.h>
#include <pthread.h>  
#include <GNCameraFeatureDefs.h>

#include "scbdefs.h"
#include "caps_base.h"
#include "fm_photoart.h"
#include "fm_autorama.h"
#include "fm_exif.h"
#include "ScaladoCameraFeatureDefs.h"
#include "GNCameraFeatureListener.h"

namespace android {

class ScaladoPanorama{
public:
	ScaladoPanorama();
	~ScaladoPanorama();
	
	CRESULT setListener(GNCameraFeatureListener* listener);
	CRESULT setCapturePath(const char* filePath);
	CRESULT track(CTSession session);
	CRESULT addImage(CTSession session, CTExifSession exifSession);
	CRESULT addImage(CTImage* image, CTSize size);
	CRESULT startAUTORAMA(int32 num);
	CRESULT stopAUTORAMA(int32 isMerge);
	void deinit();

private:
	CTbool isLockedVertical(PanoramaDirection direction);
	CTbool isLockedHorizontal(PanoramaDirection direction);
	CTbool isLockedDirection(PanoramaDirection direction);
	CRESULT mosaicImage();
	void getTranslationForWindow(PanoramaDirection direction, CTVector pDxDy, 
		CTSize size, int32* x, int32* y);
	void release();
	
	VFTracker* mTracker;
	PanoramaTransform* mTransform;
	PanoramaEngine* mEngine;
	GNCameraFeatureListener* mListener;

	int32 mImageNum;
	int32 mImageIndex;
	CTbool mEnabledTrack;
	CTImage* mLastImage;
	CTVector mLastDxDy;
	PanoramaDirection mDirection;
	const char* mFilePath;
	CTExifSession mExifSession;
	pthread_mutex_t mMutex;

	CTImage* mImageArray[PANORAMA_NUM_MAX];
};

};
#endif /* SCALADO_CAMERA_PANORAMA_H */


