/*************************************************************************************
 * 
 * Description:
 * 	Defines common variables.
 *
 * Author : wutangzhi
 * Email  : wutz@gionee.com
 * Date   : 2012-06-11
 *
 *************************************************************************************/
 
#ifndef GN_CAMERA_FEATURE_DEFS_H
#define GN_CAMERA_FEATURE_DEFS_H

#define XLOGI(fmt, args...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, fmt, ##args)
#define XLOGD(fmt, args...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, fmt, ##args)
#define XLOGE(fmt, args...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, fmt, ##args) 
	
#define PRINTE(...)	    XLOGE(__VA_ARGS__)
#define PRINTD(...)	    XLOGD(__VA_ARGS__)

////////////////////////////////////////////////////////////////////////////////////
//
// Define these macros to make MTK and Qualcomm compatiable
//
#ifdef CONFIG_GN_SCALADO_FEATURE_SUPPORT
#define GN_SCALADO_FEATURE_SUPPORT
#endif

#ifdef CONFIG_GN_ARCSOFT_FEATURE_SUPPORT
#define GN_ARCSOFT_FEATURE_SUPPORT
#endif

#ifdef CONFIG_GN_CRUNCHFISH_FEATURE_SUPPORT
#define GN_CRUNCHFISH_FEATURE_SUPPORT
#endif

#ifdef CONFIG_GN_SCALADO_LIVE_EFFECT_SUPPORT
#define GN_SCALADO_LIVE_EFFECT_SUPPORT
#endif

#ifdef CONFIG_GN_SCALADO_PICTURE_FRAME_SUPPORT
#define GN_SCALADO_PICTURE_FRAME_SUPPORT
#endif

#ifdef CONFIG_GN_SCALADO_HDR_SUPPORT
#define GN_SCALADO_HDR_SUPPORT
#endif

#ifdef CONFIG_GN_SCALADO_LOWLIGHT_SUPPORT
#define GN_SCALADO_LOWLIGHT_SUPPORT
#endif

#ifdef CONFIG_GN_SCALADO_MIRROR_SUPPORT
#define GN_SCALADO_MIRROR_SUPPORT
#endif

#ifdef CONFIG_GN_ARCSOFT_GESTURE_SHOT_SUPPORT
#define GN_ARCSOFT_GESTURE_SHOT_SUPPORT
#endif

#ifdef CONFIG_GN_CRUNCHFISH_GESTURE_DETECTION_SUPPORT
#define GN_CRUNCHFISH_GESTURE_DETECTION_SUPPORT
#endif

#ifdef CONFIG_GN_ARCSOFT_FACE_BEAUTY_SUPPORT
#define GN_ARCSOFT_FACE_BEAUTY_SUPPORT
#endif

#ifdef CONFIG_GN_ARCSOFT_AGEGENDER_DETECTION_SUPPORT
#define GN_ARCSOFT_AGEGENDER_DETECTION_SUPPORT
#endif

#ifdef CONFIG_GN_ARCSOFT_SCENE_DETECTION_SUPPORT
#define GN_ARCSOFT_SCENE_DETECTION_SUPPORT
#endif

#ifdef CONFIG_GN_ARCSOFT_NIGHT_SHOT_SUPPORT
#define GN_ARCSOFT_NIGHT_SHOT_SUPPORT
#endif

#ifdef CONFIG_GN_SCALADO_AUTORAMA_SUPPORT
#define GN_SCALADO_AUTORAMA_SUPPORT
#endif

#ifdef CONFIG_GN_ARCSOFT_LIVE_EFFECT_SUPPORT
#define GN_ARCSOFT_LIVE_EFFECT_SUPPORT
#endif

#ifdef CONFIG_GN_ARCSOFT_PICZOOM_SUPPORT
#define GN_ARCSOFT_PIC_ZOOM_SUPPORT
#endif

///////////////////////////////////////////////////////////////////////////////////

#define PICTURE_FRAME_PATH	"/system/etc/gn_camera_feature/res/picture_frame"

//This macro value is defined for bit align, which is decided according to the platform. 
// Such as QCom8974 is 64 align and MT6589 is 32 align.
#define ALIGN_FORMAT	ALIGN_TO_64	
#define ALIGN_TO_SIZE(size, align) ((size + align - 1) & ~(align - 1))

typedef enum {
    ALIGN_NONE 		= 1,
    ALIGN_TO_2 		= 2,
    ALIGN_TO_4 		= 4,
    ALIGN_TO_WORD 	= ALIGN_TO_4,
    ALIGN_TO_8 		= 8,
    ALIGN_TO_16 	= 16,
    ALIGN_TO_32 	= 32,
    ALIGN_TO_64 	= 64,
    ALIGN_TO_1K 	= 1024,
    ALIGN_TO_2K 	= 2048,
    ALIGN_TO_4K 	= 4096,
    ALIGN_TO_8K 	= 8192
} GNAlignFormat;

typedef struct {
	int width;
	int height;
	int len;
	int stride;
	int scanline;
} GNCamOffset;

typedef signed long int32;

/*************************************************************************************
 * @brief:
 * 	list all supported image formats
 *************************************************************************************/
typedef enum
{
	GN_IMG_FORMAT_NONE = 0,
	GN_IMG_FORMAT_YV12, 
	GN_IMG_FORMAT_YUV422,
	GN_IMG_FORMAT_NV21,
	GN_IMG_FORMAT_YUV420,
	GN_IMG_FORMAT_YUV420P,
	GN_IMG_FORMAT_YUV420SP,
	GN_IMG_FORMAT_YUYV,
	GN_IMG_FORMAT_RGBA8888,
	GN_IMG_FORMAT_MAX
} GNImgFormat;

/*************************************************************************************
 * @brief:
 * 	list all supported live effects
 *************************************************************************************/
typedef enum 
{
	GN_LIVE_EFFECT_NONE = 0,
	GN_LIVE_EFFECT_ANTIQUE,	 			/* antique */
	GN_LIVE_EFFECT_CARTOON,				/* cartoon */
	GN_LIVE_EFFECT_EMBOSS,				/* emboss */
	GN_LIVE_EFFECT_FLIP,				/* flip */
	GN_LIVE_EFFECT_FOG,					/* fog */
	GN_LIVE_EFFECT_GRAYSCALE,			/* grayscale */
	GN_LIVE_EFFECT_LOMO_BLUE,			/* blue */
	GN_LIVE_EFFECT_LOMO_GREEN,			/* green */
	GN_LIVE_EFFECT_LOMO_NEUTRAL,		/* neutral */
	GN_LIVE_EFFECT_LOMO_RED,			/* red */
	GN_LIVE_EFFECT_LOMO_YELLOW,			/* yellow */
	GN_LIVE_EFFECT_MAGICPEN,			/* magicpen */
	GN_LIVE_EFFECT_MILKY,				/* milky */
	GN_LIVE_EFFECT_MIRROR,				/* mirror */
	GN_LIVE_EFFECT_NEGATIVE,			/* negative */
	GN_LIVE_EFFECT_OILY,				/* oily */
	GN_LIVE_EFFECT_PAINT,				/* paint */
	GN_LIVE_EFFECT_SEPIA,				/* sepia */
	GN_LIVE_EFFECT_SKETCH_COLOR,		/* sketch color */
	GN_LIVE_EFFECT_SKETCH_GRAY,			/* sketch gray */
	GN_LIVE_EFFECT_SOLARIZE,			/* solarize */
	GN_LIVE_EFFECT_STAMP,				/* stamp */
	GN_LIVE_EFFECT_DOF,					/* dof */
	GN_LIVE_EFFECT_VIGNETTING,			/* vignetting */
	GN_LIVE_EFFECT_WARP_FISHEYE,		/* fisheye */
	GN_LIVE_EFFECT_WARP_ALIENSCUM,		/* alienscum */
	GN_LIVE_EFFECT_WARP_BIGBUPPA,		/* bigbuppa */
	GN_LIVE_EFFECT_WARP_BOOZIEBOWL,		/* booziebowl */
	GN_LIVE_EFFECT_WARP_CONEHEAD,		/* conehead */
	GN_LIVE_EFFECT_WARP_FUNKYFRESH,		/* funkyfresh */
	GN_LIVE_EFFECT_WARP_JELLYBELLY,		/* jellybelly */
	GN_LIVE_EFFECT_WARP_PETTYPETIT,		/* pettypetit */
	GN_LIVE_EFFECT_WARP_EYEBALLEDEVY,	/* eyeballedevy */
	GN_LIVE_EFFECT_WARP_SPEEDYWEED,		/* speedyweed */
	GN_LIVE_EFFECT_WARP_MOSAIC,			/* mosaic */
	GN_LIVE_EFFECT_WARP_FROST,			/* frost */
	GN_LIVE_EFFECT_WARP_MOON_LIGHT,		/* moon light */
	GN_LIVE_EFFECT_WARP_NOISE,			/* denoise */
	GN_LIVE_EFFECT_WARP_WATER_COLOR,	/* water color */
	GN_LIVE_EFFECT_FLEETINGTIME,		/* fleeting time */
	GN_LIVE_EFFECT_CRAYON,				/* crayon */
	GN_LIVE_EFFECT_SNOWFLAKES,			/* snow flakes */
	GN_LIVE_EFFECT_LIGHTBEAM,			/* light beam */
	GN_LIVE_EFFECT_REFLECTION,			/* relection */
	GN_LIVE_EFFECT_SUNSET,				/* sunset */
	GN_LIVE_EFFECT_REVERSAL,			/* reversal */
	GN_LIVE_EFFECT_WARMLOMO,			/* warm lomo */
	GN_LIVE_EFFECT_COLDLOMO,			/* cold lomo */
	GN_LIVE_EFFECT_SOFTPINK,			/* softpink */
	GN_LIVE_EFFECT_JAPANBACKLIGHT,		/* japan backlight */
	GN_LIVE_EFFECT_COSMETOLOGY_BACKLIGHT, /* cosmetology backlight */
	GN_LIVE_EFFECT_FINEFOOD,  			/* find food*/
	GN_LIVE_EFFECT_BLACKWHITE,			/* black white*/
	GN_LIVE_EFFECT_MAX
} GNLiveEffect_t;

/*************************************************************************************
 * @brief:
 * 	list HDR states.
 *************************************************************************************/
typedef enum
{
	GN_HDR_OFF = 0,
	GN_HDR_ON,
	GN_HDR_MAX
} GNHdr_t;

/*************************************************************************************
 * @brief:
 * 	list Lowlight states.
 *************************************************************************************/
typedef enum 
{
	GN_LOWLIGHT_OFF = 0,
	GN_LOWLIGHT_ON,
	GN_LOWLIGHT_MAX
} GNLowlight_t;

/*************************************************************************************
 * @brief:
 * 	list face beauty states.
 *************************************************************************************/
typedef enum 
{
	GN_FACEBEAUTY_OFF 		= 0,
	GN_FACEBEAUTY_LOW 		= 1,
	GN_FACEBEAUTY_MEDIUM 	= 6,
	GN_FACEBEAUTY_HIGH 		= 12,
//Gionee <zhuangxiaojian> <2013-08-20> modify for CR00867956 begin
#ifdef ORIGINAL_VERSION
#else
	GN_FACEBEAUTY_ON,
#endif
//Gionee <zhuangxiaojian> <2013-08-20> modify for CR00867956 begin
	GN_FACEBEAUTY_MAX
} GNFaceBeauty_t;

/*************************************************************************************
 * @brief:
 * 	list gesture shot states.
 *************************************************************************************/
typedef enum
{
	GN_GESTURE_SHOT_OFF = 0,
	GN_GESTURE_SHOT_ON,
	GN_GESTURE_SHOT_MAX
} GNGestureShot_t;

/*************************************************************************************
 * @brief:
 * 	list mirror states.
 *************************************************************************************/
typedef enum
{
	GN_MIRROR_OFF = 0,
	GN_MIRROR_ON,
	GN_MIRROR_MAX
} GNMirror_t;

/*************************************************************************************
 * @brief:
 * 	list Lowlight states.
 *************************************************************************************/
typedef enum 
{
	GN_PANORAMA_OFF = 0,
	GN_PANORAMA_ON,
	GN_PANORAMA_MAX
} GNPanorama_t;

/*************************************************************************************
 * @brief:
 * 	list gesture detection types.
 *************************************************************************************/
typedef enum
{
	GN_GESTURE_DETECTION_NONE				= 0,
	GN_GESTURE_DETECTION_OPEN_HAND_PRESENCE,
	GN_GESTURE_DETECTION_FACE_PRESENCE,
	GN_GESTURE_DETECTION_FIST_PRESENCE,
	GN_GESTURE_DETECTION_MAX
} GNGestureDetection_t;

/*************************************************************************************
 * @brief:
 * 	list scene detection states.
 *************************************************************************************/
typedef enum
{
	GN_SCENE_DETECTION_OFF = 0,
	GN_SCENE_DETECTION_ON,
	GN_SCENE_DETECTION_MAX
} GNSceneDetection_t;

/*************************************************************************************
 * @brief:
 * 	list scene detection states.
 *************************************************************************************/
typedef enum
{
	GN_NIGHT_SHOT_OFF = 0,
	GN_NIGHT_SHOT_ON,
	GN_NIGHT_SHOT_MAX
} GNNightShot_t;


/*************************************************************************************
 * @brief:
 * 	list all supported features of gionne camera.
 *************************************************************************************/
typedef enum 
{
	GN_CAMERA_FEATURE_NONE 				= 0,
	GN_CAMERA_FEATURE_HDR				= 1 << 1,
	GN_CAMERA_FEATURE_LOWLIGHT			= 1 << 2,
	GN_CAMERA_FEATURE_EFFECT			= 1 << 3,
	GN_CAMERA_FEATURE_PICTURE_FREAME	= 1 << 4,
	GN_CAMERA_FEATURE_PANORAMA			= 1 << 5,
	GN_CAMERA_FEATURE_FACE_BEAUTY		= 1 << 6,
	GN_CAMERA_FEATURE_GESTURE_SHOT		= 1 << 7,
	GN_CAMERA_FEATURE_GESTURE_DETECTION = 1 << 8,
	GN_CAMERA_FEATUER_MIRROR			= 1 << 9,
	GN_CAMERA_FEATUER_SCENE_DETECTION	= 1 << 10,
	GN_CAMERA_FEATUER_NIGHT_SHOT		= 1 << 11,
	GN_CAMERA_FEATUER_AGEGENDER_DETECTION = 1 << 12,
	GN_CAMERA_FEATURE_PIC_ZOOM			= 1 << 13,
} GNCameraFeature_t;

/*************************************************************************************
 * @brief:
 * 	list all profiles of gionne camera.
 *************************************************************************************/
typedef enum
{
	GN_CAMERA_PROFILE_SCALADO_HDR					= 1 << 0,
	GN_CAMERA_PROFILE_SCALADO_LOWLIGHT				= 1 << 1,
	GN_CAMERA_PROFILE_SCALADO_EFFECT				= 1 << 2,
	GN_CAMERA_PROFILE_SCALADO_PICTURE_FRAME 		= 1 << 3,
	GN_CAMERA_PROFILE_SCALADO_PANORAMA				= 1 << 4,
	GN_CAMERA_PROFILE_SCALADO_MIRROR				= 1 << 5,
	GN_CAMERA_PROFILE_ARCSOFT_FACE_BEAUTY			= 1 << 6,
	GN_CAMERA_PROFILE_ARCSOFT_GESTURE_SHOT			= 1 << 7,
	GN_CAMERA_PROFILE_ARCSOFT_SCENE_DETECTION 		= 1 << 8,
	GN_CAMERA_PROFILE_ARCSOFT_NIGHT_SHOT	 		= 1 << 9,
	GN_CAMERA_PROFILE_ARCSOFT_EFFECT				= 1 << 10,
	GN_CAMERA_PROFILE_CRUNCHFISH_GESTURE_DETECTION 	= 1 << 11,
	GN_CAMERA_PROFILE_AGEGENDER_DETECTION			= 1 << 12,
	GN_CAMERA_PROFILE_ARCSOFT_PIC_ZOOM				= 1 << 13,
} GNCameraProfile_t;

typedef enum
{
	GN_CAMERA_FACE_FEATURE_NONE					= 0,
	GN_CAMERA_FACE_FEATURE_FACEBEAUTY			= 1 << 0,
	GN_CAMERA_FACE_FEATURE_AGEGENDER_DETECTION	= 1 << 1,
}GNFaceProcessFeature_t;

/*************************************************************************************
 * @brief:
 * 	list all supported camera types.
 *************************************************************************************/
typedef enum
{
	GN_CAMERA_TYPE_BACK = 0,
	GN_CAMERA_TYPE_FRONT = 1,
	GN_CAMERA_TYPE_NUM
} GNCameraType_t;

/*************************************************************************************
 * @brief:
 * 	list all supported panorama message types.
 *************************************************************************************/
typedef enum
{
	GN_PANORAMA_MSG_TYPE_CAPTURE 		= 1 << 0,
	GN_PANORAMA_MSG_TYPE_DIR_CHANGED 	= 1 << 1,
	GN_PANORAMA_MSG_TYPE_XY 			= 1 << 2,
} GNPanoramaMsgType_t;

/*************************************************************************************
 * @brief:
 * 	list all supported camera message types.
 *************************************************************************************/
typedef enum
{
	GN_CAMERA_MSG_TYPE_PANORAMA 			= 1 << 0,
	GN_CAMERA_SMG_TYPE_GESTURE_SHOT 		= 1 << 1,
	GN_CAMERA_MSG_TYPE_GESTURE_DETECTION 	= 1 << 2,
	GN_CAMERA_MSG_TYPE_SCENE_DETECTION		= 1 << 3,
	GN_CAMERA_MSG_TYPE_AGEGENDER_DETECTION	= 1 << 4,
} GNCameraMsgType_t;

/*************************************************************************************
 * @brief:
 * 	list all supported scene detection type.
 *************************************************************************************/
typedef enum
{
	GN_CAMERA_SCENE_DETECTION_TYPE_AUTO 			= 1,
	GN_CAMERA_SCENE_DETECTION_TYPE_PORTRAIT 		= 2,
	GN_CAMERA_SCENE_DETECTION_TYPE_CLOSEUP  		= 3,
	GN_CAMERA_SCENE_DETECTION_TYPE_NIGHT			= 4,
	GN_CAMERA_SCENE_DETECTION_TYPE_PORTRAIT_NIGHT	= 5,
	GN_CAMERA_SCENE_DETECTION_TYPE_BACKLIT			= 6,
	GN_CAMERA_SCENE_DETECTION_TYPE_PORTRAIT_BACKLIT	= 7,
	GN_CAMERA_SCENE_DETECTION_TYPE_TEXT				= 8,
	GN_CAMERA_SCENE_DETECTION_TYPE_SPORT			= 9,
	GN_CAMERA_SCENE_DETECTION_TYPE_GOURMET			= 10,
} GNCameraSceneDetectionType_t;

/*************************************************************************************
 * @brief:
 * 	define the face beauty parameters.
 *************************************************************************************/
#define MAX_MULTI_FACE_NUM 8

typedef struct _AgeGenderParam {
    int faceId;
    int feautyLevel;
} AgeGenderParam_t;

typedef struct _FaceBeautyLevelParam {
	int faceBeautyLevel;	//0~11
	int slenderFaceLevel;
	int skinSoftenLevel;
	int eyeEnlargmentLevel;
} FaceBeautyLevelParam_t;

typedef enum _FaceBeautyMode {
	GN_FACEBEATUY_MODE_NONE,
	GN_FACEBEAUTY_MODE_DEFAULT,
	GN_FACEBEAUTY_MODE_AGEGENDER,
	GN_FACEBEAUTY_MODE_MAX,
} FaceBeautyMode_t;

typedef struct _FaceBeautyParam {
	int faceBeautyMode;
	int	faceBeautyState;	//on or off
	AgeGenderParam_t ageGenderParam[MAX_MULTI_FACE_NUM];
	FaceBeautyLevelParam_t faceBeautyLevelParam;
	int faceNum;
} FaceBeautyParam;

typedef enum
{
	GN_AGEGENDER_DETECTION_OFF = 0,
	GN_AGEGENDER_DETECTION_ON,
	GN_AGEGENDER_DETECTION_MAX
} GNAgeGenderDetection_t;

typedef struct _FaceRect {
	long left;
	long top;
	long right;
	long bottom;
} FaceRect_t;

typedef struct _AgeGenderResult {
	int ageResult[MAX_MULTI_FACE_NUM];
	int genderResult[MAX_MULTI_FACE_NUM];
	FaceRect_t faceRect[MAX_MULTI_FACE_NUM];
	int faceNumber;
} AgeGenderResult_t;

/*************************************************************************************
 * @brief:
 * 	list pic zoom parameters.
 *************************************************************************************/
typedef enum 
{
	GN_PIC_ZOOM_OFF 	= 0,
	GN_PIC_ZOOM_ON 		= 1,
	GN_PIC_ZOOM_MAX
} GNPicZoom_t;

typedef struct _PicZoomParam {
	float 		scaleRatio;
	GNPicZoom_t picZoomMode;
} PicZoomParam;

#endif /* GN_CAMERA_FEATURE_DEFS_H */

