/*************************************************************************************
 * 
 * Description:
 * 	Defines scalado APIs for camera HAL.
 *
 * Author : wutangzhi
 * Email  : wutz@gionee.com
 * Date   : 2012-06-11
 *
 *************************************************************************************/

#ifndef ANDROID_CAMERA_FEATURE_H
#define ANDROID_CAMERA_FEATURE_H

#include "scbdefs.h"
#include "caps_base.h"
#include "ScaladoLiveEffect.h"
#include "ScaladoCameraFeatureDefs.h"
#include "ScaladoHdrLowlight.h"
#include "ScaladoPictureFrame.h"
#include "ScaladoPanorama.h"

#include <GNCameraFeatureBase.h>

namespace android {                  

class ScaladoCameraFeature : public GNCameraFeatureBase {

public:
	ScaladoCameraFeature();
	~ScaladoCameraFeature();

	static ScaladoCameraFeature* createInstance();
	virtual void destroyInstance();

	virtual int32 init();
	virtual void  deinit();
	virtual void  setCameraType(GNCameraType_t cameraType);
	virtual int32 setCameraListener(GNCameraFeatureListener* listener);
	virtual int32 setCapturePath(const char* filePath);
	virtual int32 initPreviewSize(int width, int height, GNImgFormat format);
	virtual int32 processPreview(void* inputBuffer, int size, int mask);
	virtual int32 processPicture(void* inputBuffer, int* size, int mask);
	virtual int32 processRaw(void* inputBuffer, int size, int width, int height, GNImgFormat format, int mask);
	virtual int32 setEffect(GNLiveEffect_t effect);
	virtual int32 setPictureFrame(char* frameName);
	virtual int32 setHdr(GNHdr_t hdrMode);
	virtual int32 setLowlight(GNLowlight_t lowlightMode);
	virtual int32 startAUTORAMA(int32 num);
	virtual int32 stopAUTORAMA(int32 isMerge);
	virtual int32 setBurstCnt(GNCameraFeature_t cameraFeature, int count);
	virtual int32 setOrientation(int orientation);
	virtual int32 setMirror(GNMirror_t mirrorMode);

private:
	CRESULT applyEffect(CTSession session, CTSize size);
	CRESULT applyPictureFrame(CTSession session);
	CRESULT applyHDR(CTSession session, CTStream* outputStream, CTExifSession exif);
	CRESULT applyLowlight(CTSession session, CTStream* outputStream, CTExifSession exif);
	CRESULT applyAUTORAMA(CTSession session, CTExifSession exif);
	CRESULT applyMirror(CTSession session, CTSize size);
	CRESULT copyBuffer(void* dst, void* src, int size, int width, int height, CTColormode format, bool isCopyIn);
	CTColormode mapPixelFormatToScalado(GNImgFormat format);
	void dump(CTSession session, CTSize size);
	
	CTSession mSession;
	CTImage* mInputImage;
	CTImage* mOutImage;

	GNImgFormat mFormat;
	CTSize mPreviewSize;
	int mPreviewBufferSize;
	int mGNCameraFeature;
	char mFilePath[512];

	ScaladoLiveEffect mScaladoLiveEffect; 
	GNLiveEffect_t mEffectStyle;

	ScaladoHdrLowlight mScaladoHdrLowlight;
	
	ScaladoPictureFrame mScaladoPictureFrame;
	CTchar mFrameName[256];

	ScaladoPanorama mScaladoPanorama;

	GNCameraType_t mCameraType; 

	GNCameraFeatureListener* mListener;

	int mOrientation;

	//wutz 
	pthread_mutex_t mMutex;
};
};

#endif /* ANDROID_CAMERAFEATURE_H */
