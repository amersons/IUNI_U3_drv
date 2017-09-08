/*************************************************************************************
 * 
 * Description:
 * 	Defines common interface of gionee feature for camera HAL.
 *
 * Author : wutangzhi
 * Email  : wutz@gionee.com
 * Date   : 2012-06-11
 *
 *************************************************************************************/

#ifndef I_GN_CAMERA_FEATURE_H
#define I_GN_CAMERA_FEATURE_H

#include <utils/String8.h>
#include <utils/Errors.h>

#include "GNCameraFeatureDefs.h"
#include "GNCameraFeatureListener.h"

namespace android {         

class IGNCameraFeature {

public:
	/*************************************************************************************
	 * @brief:
	 * 	Set camera type.
	 *
     	 * @param id
	 * 	Specify camera type in @GNCameraType_t.
	 *
       * @return
	 *	- 0 if function succeds.
	 *	- Other number, if the funtion fails. 
	 *************************************************************************************/
	virtual void setCameraType(GNCameraType_t cameraType) = 0;

	/*************************************************************************************
	 * @brief:
	 * 	Register camera messages.
	 *
	 * @param listener
	 *	Callback messages to HAL.
	 *
     	 * @param msgType
	 * 	Specify messag type in @GNCameraMsgType.
	 *
       * @return
	 *	- 0 if function succeds.
	 *	- Other number, if the funtion fails. 
	 *************************************************************************************/
	virtual int32 setCameraListener(GNCameraFeatureListener* listener) = 0;

	/*************************************************************************************
	 * @brief:
	 * 	Set picture path for capturing..
	 *
	 * @param filePath
	 *	A pointer to picture path.
	 *
       * @return
	 *	- 0 if function succeds.
	 *	- Other number, if the funtion fails. 
	 *************************************************************************************/
	virtual int32 setCapturePath(const char* filePath) = 0;

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
	 *	- Other number, if the funtion fails. 
	 *************************************************************************************/
	virtual int32 initPreviewSize(int width, int height, GNImgFormat format)= 0;

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
	 * @param mask
	 *     The mask to the GNCameraFeature_t
	 *
       * @return
	 *	- 0 if function succeds 
	 *	- Other number, if the funtion fails. 
	 *************************************************************************************/
	virtual int32 processPreview(void* inputBuffer, int size, int mask) = 0;

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
	 * @param mask
	 *     The mask to the GNCameraFeature_t
	 *
        * @return
	 *	- 0 if function succeds
	 *	- Other number, if the funtion fails. 
	 *************************************************************************************/
	virtual int32 processPicture(void* inputBuffer, int* size, int mask) = 0;

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
	* @param s8Format
	* 	The raw format to the camera.
	*
	* @param mask
	*     The mask to the GNCameraFeature_t
	*
	* @return
	*	- 0 if function succeds and format is identified
	*	- Other number, if the funtion fails. 
	*************************************************************************************/
	virtual int32 processRaw(
		void* inputBuffer, int size, int width, int height, GNImgFormat format, int mask) = 0;

	/*************************************************************************************
	 * @brief:
	 * 	Set live effect feature to camera
	 *
     	 * @param effect
	 * 	Specify some effect in @GNLiveEffect_t
	 *
       * @return
	 *	- 0 if function succeds and effect is identified
	 *	- Other number, if the funtion fails. 
	 *************************************************************************************/
	virtual int32 setEffect(GNLiveEffect_t effect) = 0;
	
	/*************************************************************************************
	* @brief:
	*	Set picture frame to camera
	*
	* @param frameName
	*	A pointer to a frame name.
	*
	* @return
	*	- 0 if function succeds and frameName is valid.
	*	- Other number, if the funtion fails. 
	*************************************************************************************/
	virtual int32 setPictureFrame(char* frameName) = 0;

	/*************************************************************************************
	 * @brief:
	 * 	Set HDR feature to camera
	 *
	 * @param hdrMode
	 * 	Specify HDR states in @GNHdr_t
	 *
	 * @return
	 *	- 0 if function succeds and hdrMode is identified
	 *	- Other number, if the funtion fails. 
	 *************************************************************************************/
	virtual int32 setHdr(GNHdr_t hdrMode) = 0;

	/*************************************************************************************
	 * @brief:
	 * 	Set lowlight feature to camera
	 *
	 * @param lowlightMode
	 * 	Specify some effect in @GNLowlight_t
	 *
	 * @return
	 *	- 0 if function succeds and lowlightMode is identified
	 *	- Other number, if the funtion fails. 
	 *************************************************************************************/
	virtual int32 setLowlight(GNLowlight_t lowlightMode) = 0;

	/*************************************************************************************
	 * @brief:
	 * 	Set face beauty feature to camera
	 *
	 * @param faceBeautyMode
	 * 	Specify some effect in @FaceBeautyParam
	 *
	 * @return
	 *	- 0 if function succeds and faceBeautyMode is identified
	 *	- Other number, if the funtion fails. 
	 *************************************************************************************/
	virtual int32 setFaceBeauty(FaceBeautyParam const faceBeautyParam) = 0;

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
	virtual int32 setAgeGenderDetection(GNAgeGenderDetection_t const ageGenderDetection) = 0;

	/*************************************************************************************
	 * @brief:
	 * 	Set gesture shot feature to camera
	 *
	 * @param gestureShotMode
	 * 	Specify some effect in @GNGestureShot_t
	 *
	 * @return
	 *	- 0 if function succeds and gestureShotMode is identified
	 *	- Other number, if the funtion fails. 
	 *************************************************************************************/
	virtual int32 setGestureShot(GNGestureShot_t gestureShotMode) = 0;

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
	virtual int32 setGestureDetection(GNGestureDetection_t gestureDetectionMode) = 0;

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
	virtual int32 setMirror(GNMirror_t mirrorMode) = 0;

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
	virtual int32 setSceneDetection(GNSceneDetection_t sceneDetectionMode) = 0;

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
	virtual int32 setNightShot(GNNightShot_t nightShotMode) = 0;

	/*************************************************************************************
	 * @brief:
	 * 	Set piczoom mode
	 *
	 * @param picZoomParam
	 * 	Specify some mode in @PicZoomParam
	 *
	 * @return
	 *	- 0 if function succeds and picZoomParam is identified
	 *	- Other number, if the funtion fails. 
	 *************************************************************************************/
	virtual int32 setPicZoom(PicZoomParam const picZoomParam) = 0;
	
	/*************************************************************************************
	 * @brief:
	 * 	Start to capture in panorama mode.
	 *
	 * @param num
	 * 	Start to capture number of images of panorama.
	 *
	 * @return
	 *	- 0 if function succeds and num > 0.
	 *	- Other number, if the funtion fails. 
	 *************************************************************************************/
	virtual int32 startAUTORAMA(int32 num) = 0;

	/*************************************************************************************
	 * @brief:
	 * 	stop to capture in panorama mode.
	 *
	 * @param isMerge
	 * 	Stop auto panorama, if isMerge isn't 0, there will be a callback when merge is done.
	 *
	 * @return
	 *	- 0 if function succeds.
	 *	- Other number, if the funtion fails. 
	 *************************************************************************************/
	virtual int32 stopAUTORAMA(int32 isMerge) = 0;

	/*************************************************************************************
	 * @brief:
	 * 	set burst count accroding to camera feature.
	 *
       * @param cameraFeature
	 * 	Specify some feature in @GNCameraFeature_t
	 *
       * @return
	 *	- 0 if function succeds and cameraFeature is identified
	 *	- Other number, if the funtion fails. 
	 *************************************************************************************/
	virtual int32 setBurstCnt(GNCameraFeature_t cameraFeature, int count) = 0;

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
	virtual int32 getBurstCnt(GNCameraFeature_t cameraFeature) = 0;

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
	virtual int32 setOrientation(int orientation) = 0;

	/*************************************************************************************
	 * @brief:
	 * 	initialize the object.
	 *
       * @return
	 * 	-
	 *************************************************************************************/
	virtual int32 init() = 0;

	/*************************************************************************************
	 * @brief:
	 * 	Release object or memory.
	 *
       * @return
	 * 	-
	 *************************************************************************************/
	virtual void deinit() = 0;

	/*************************************************************************************
	 * @brief:
	 * 	destroy the instance.
	 *
       * @return
	 * 	-
	 *************************************************************************************/
	virtual void destroyInstance() = 0;

	virtual ~IGNCameraFeature() {};
};
};

#endif /* I_GN_CAMERA_FEATURE_H */
