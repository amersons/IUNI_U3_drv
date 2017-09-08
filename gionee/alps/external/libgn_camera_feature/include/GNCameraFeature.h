/*************************************************************************************
 * 
 * Description:
 * 	Defines gionee feature APIs for camera HAL.
 *
 * Author : wutangzhi
 * Email  : wutz@gionee.com
 * Date   : 2012-06-11
 *
 *************************************************************************************/

#ifndef GN_CAMERA_FEATURE_H
#define GN_CAMERA_FEATURE_H

#include <utils/String8.h>
#include <utils/Errors.h>

#include "GNCameraFeatureDefs.h"
#include "IGNCameraFeature.h"
#include "GNCameraFeatureListener.h"

namespace android {         

class GNCameraFeature {

public:
	GNCameraFeature();

	/*************************************************************************************
	 * @brief:
	 * 	create GNCameraFeature instance.
	 *
       * @return
	 *	- the pointer points the GNCameraFeature.
	 *************************************************************************************/
	static GNCameraFeature* createInstance();

	/*************************************************************************************
	 * @brief:
	 * 	destroy GNCameraFeature instance.
	 *
       * @return
	 *	-
	 *************************************************************************************/
	void destroyInstance();

	/*************************************************************************************
	 * @brief:
	 * 	initialize the object.
	 *
       * @return
	 *	- 0 if function succeds and orientation is valid
	 *	- Other number, if the funtion fails.
	 *************************************************************************************/
	int32 init();

	/*************************************************************************************
	 * @brief:
	 * 	Release object or memory.
	 *
	 * @return
	 * 	-
	 *************************************************************************************/
	void deinit();

	/*************************************************************************************
	 * @brief:
	 * 	Set camera type.
	 *
     	 * @param id
	 * 	Specify camera type in @GNCameraType_t.
	 *
       * @return
	 *	- 0 if function succeds.
	 *	- Other number, if the cuntion fails. 
	 *************************************************************************************/
	void setCameraType(GNCameraType_t cameraType);

	/*************************************************************************************
	 * @brief:
	 * 	Set camera listener.
	 *
	 * @param listener
	 *	Callback messages to HAL.
	 *
       * @return
	 *	- 0 if function succeds.
	 *	- Other number, if the cuntion fails. 
	 *************************************************************************************/
	int32 setCameraListener(GNCameraFeatureListener* listener);

	/*************************************************************************************
	 * @brief:
	 * 	Set picture path for capturing..
	 *
	 * @param filePath
	 *	A pointer to picture path.
	 *
       * @return
	 *	- 0 if function succeds.
	 *	- Other number, if the cuntion fails. 
	 *************************************************************************************/
	int32 setCapturePath(const char* filePath);
		
	/*************************************************************************************
	 * @brief:
	 * 	Initialize preview
	 *
	 * @param width
	 * 	The preview width to the camera.
	 *
	 * @param height
	 * 	The preview height to the camera.
	 *
	 * @param format
	 * 	The preview format to the camera.
	 *
	 * @return
	 *	- 0 if function succeds and format is identified
	 *	- Other number, if the cuntion fails. 
	 *************************************************************************************/
	int32 initPreviewSize(int width, int height, GNImgFormat format);

	/*************************************************************************************
	 * @brief:
	 * 	Process preview data according to the specifical feature.
	 *
	 * @param inputBuffer
	 * 	A pointer to a stream buffer containing preview data.
	 *
	 * @param size 
	 * 	The size to the input stream buffer.
	 *
	 * @return
	 *	- 0 if function succeds 
	 *	- Other number, if the cuntion fails. 
	 *************************************************************************************/
	int32 processPreview(void* inputBuffer, int size, int mask);

	/*************************************************************************************
	 * @brief:
	 * 	Process capture data according to the specifical feature.
	 *
	 * @param inputBuffer
	 * 	A pointer to a stream buffer containing capture data.
	 *
	 * @param size 
	 * 	A pointer to the size of input stream buffer.
	 *
	 * @return
	 *	- 0 if function succeds
	 *	- Other number, if the cuntion fails. 
	 *************************************************************************************/
	int32 processPicture(void* inputBuffer, int* size, int mask);

	/*************************************************************************************
	 * @brief:
	 * 	Process raw data according to the specifical feature.
	 *
	 * @param inputBuffer
	 * 	A pointer to a stream buffer containing raw data.
	 *
	 * @param size 
	 * 	The size to the input stream buffer.
	 *
	 * @param width
	 * 	The raw width to the camera.
	 *
	 * @param height
	 * 	The raw height to the camera.
	 *
	 * @param format
	 * 	The raw format to the camera.
	 *
	 * @return
	 *	- 0 if function succeds and format is identified
	 *	- Other number, if the cuntion fails. 
	 *************************************************************************************/
	int32 processRaw(
		void* inputBuffer, int size, int width, int height, GNImgFormat format, int mask);

	/*************************************************************************************
	 * @brief:
	 * 	Set live effect feature to camera
	 *
	 * @param effect
	 * 	Specify some effect in @GNLiveEffect_t
	 *
	 * @return
	 *	- 0 if function succeds and effect is identified
	 *	- Other number, if the cuntion fails. 
	 *************************************************************************************/
	int32 setEffect(GNLiveEffect_t effect);

	/*************************************************************************************
	* @brief:
	*	Set picture frame to camera
	*
	* @param inputBuffer
	*	A pointer to a stream buffer containing picture data.
	*
	* @param frameName
	*	A pointer to a frame name.
	*
	* @return
	*	- 0 if function succeds and frameName is valid.
	*	- Other number, if the cuntion fails. 
	*************************************************************************************/
	int32 setPictureFrame(char* frameName);

	/*************************************************************************************
	 * @brief:
	 * 	Set HDR feature to camera
	 *
	 * @param effect
	 * 	Specify HDR states in @GNHdr_t
	 *
	 * @return
	 *	- 0 if function succeds and hdrMode is identified
	 *	- Other number, if the cuntion fails. 
	 *************************************************************************************/
	int32 setHdr(GNHdr_t hdrMode);

	/*************************************************************************************
	 * @brief:
	 * 	Set lowlight feature to camera
	 *
	 * @param effect
	 * 	Specify some effect in @GNLowlight_t
	 *
	 * @return
	 *	- 0 if function succeds and lowlightMode is identified
	 *	- Other number, if the cuntion fails. 
	 *************************************************************************************/
	int32 setLowlight(GNLowlight_t lowlightMode);

	/*************************************************************************************
	 * @brief:
	 * 	Set face beauty feature to camera
	 *
	 * @param effect
	 * 	Specify some effect in @FaceBeautyParam
	 *
	 * @return
	 *	- 0 if function succeds and faceBeautyMode is identified
	 *	- Other number, if the funtion fails. 
	 *************************************************************************************/
	int32 setFaceBeauty(FaceBeautyParam const faceBeautyParam);

	/*************************************************************************************
	 * @brief:
	 * 	Set age gender detection feature to camera
	 *
	 * @param effect
	 * 	Specify mode in @GNAgeGenderDetection_t
	 *
	 * @return
	 *	- 0 if function succeds and ageGenderDetection is identified
	 *	- Other number, if the funtion fails. 
	 *************************************************************************************/
	int32 setAgeGenderDetection(GNAgeGenderDetection_t const ageGenderDetection);

	/*************************************************************************************
	 * @brief:
	 * 	Set gesture shot feature to camera
	 *
	 * @param effect
	 * 	Specify some effect in @GNGestureShot_t
	 *
	 * @return
	 *	- 0 if function succeds and gestureShotMode is identified
	 *	- Other number, if the funtion fails. 
	 *************************************************************************************/
	int32 setGestureShot(GNGestureShot_t gestureShotMode);

	/*************************************************************************************
	 * @brief:
	 * 	Set gesture detection feature to camera. When enable special gesture detection, the gesture detection module 
	 *	will parse the input stream and callback the gesture data to HAL.
	 *
	 * @param gestureDetectionMode
	 * 	Specify some effect in @GNGestureDetection_t
	 *
	 * @return
	 *	- 0 if function succeds and gestureDetectionMode is identified
	 *	- Other number, if the funtion fails. 
	 *************************************************************************************/
	int32 setGestureDetection(GNGestureDetection_t gestureDetectionMode);

	/*************************************************************************************
	 * @brief:
	 * 	Set mirror effect
	 *
	 * @param mirrorMode
	 * 	Specify some effect in @GNMirror_t
	 *
	 * @return
	 *	- 0 if function succeds and mirrorMode is identified
	 *	- Other number, if the funtion fails. 
	 *************************************************************************************/
	int32 setMirror(GNMirror_t mirrorMode);

	/*************************************************************************************
	 * @brief:
	 * 	Set scene detection
	 *
	 * @param sceneDetectionMode
	 * 	Specify some mode in @GNSceneDetection_t
	 *
	 * @return
	 *	- 0 if function succeds and sceneDetectionMode is identified
	 *	- Other number, if the funtion fails. 
	 *************************************************************************************/
	int32 setSceneDetection(GNSceneDetection_t sceneDetectionMode);

	/*************************************************************************************
	 * @brief:
	 * 	Set night shot
	 *
	 * @param nightShotMode
	 * 	Specify some mode in @GNNightShot_t
	 *
	 * @return
	 *	- 0 if function succeds and nightShotMode is identified
	 *	- Other number, if the funtion fails. 
	 *************************************************************************************/
	int32 setNightShot(GNNightShot_t nightShotMode);

	/*************************************************************************************
	 * @brief:
	 * 	Set pic zoom
	 *
	 * @param effect
	 * 	Specify some effect in @PicZoomParam
	 *
	 * @return
	 *	- 0 if function succeds and picZoomParam is identified
	 *	- Other number, if the funtion fails. 
	 *************************************************************************************/
	int32 setPicZoom(PicZoomParam const picZoomParam);
	
	/*************************************************************************************
	 * @brief:
	 * 	Start to capture in panorama mode.
	 *
	 * @param num
	 * 	Start to capture number of images of panorama.
	 *
	 * @return
	 *	- 0 if function succeds and num > 0.
	 *	- Other number, if the cuntion fails. 
	 *************************************************************************************/
	int32 startAUTORAMA(int32 num);

	/*************************************************************************************
	 * @brief:
	 * 	stop to capture in panorama mode.
	 *
	 * @param isMerge
	 * 	Stop auto panorama, if isMerge isn't 0, there will be a callback when merge is done.
	 *
	 * @return
	 *	- 0 if function succeds.
	 *	- Other number, if the cuntion fails. 
	 *************************************************************************************/
	int32 stopAUTORAMA(int32 isMerge);

	/*************************************************************************************
	 * @brief:
	 * 	set burst count accroding to camera feature.
	 *
	   * @param cameraFeature
	 * 	Specify some feature in @GNCameraFeature_t
	 *
	   * @return
	 *	- 0 if function succeds and cameraFeature is identified
	 *	- Other number, if the cuntion fails. 
	 *************************************************************************************/
	int32 setBurstCnt(GNCameraFeature_t cameraFeature, int count);

	/*************************************************************************************
	 * @brief:
	 * 	get burst count accroding to camera feature.
	 *
       * @param cameraFeature
	 * 	Specify some feature in @GNCameraFeature_t
	 *
       * @return
	 *	- 0 if function succeds and cameraFeature is identified
	 *	- Other number, if the funtion fails. 
	 *************************************************************************************/
	int32 getBurstCnt(GNCameraFeature_t cameraFeature);

	/*************************************************************************************
	 * @brief:
	 * 	set current display orientation.
	 *
       * @param orientation
	 * 	0/90/180/270
	 *
       * @return
	 *	- 0 if function succeds and orientation is valid
	 *	- Other number, if the funtion fails. 
	 *************************************************************************************/
	int32 setOrientation(int orientation);

	/*************************************************************************************
	 * @brief:
	 * 	get the feature mask.
	 *
        * @return
	 *	- mGNCameraFeatureMask
	 *************************************************************************************/
	int32 getFeatureMask() {return mGNCameraFeatureMask;};

private:
	int32 getProfileMask(int32 featureMask);
	void  updateFeatureMask(int32 flag, int32 mask);
	
	IGNCameraFeature* mScaladoCameraFeature;
	IGNCameraFeature* mArcsoftCameraFeature;
	IGNCameraFeature* mCrunchfishCameraFeature;

	int32 mGNCameraProfile;
	int32 mGNCameraFeatureMask;
};
};

#endif /* GN_CAMERA_FEATURE_H */
