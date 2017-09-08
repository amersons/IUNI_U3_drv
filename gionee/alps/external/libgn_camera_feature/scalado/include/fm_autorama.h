/*  . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
.                                                                             .
.    (c) 2000-2010 Scalado AB. All rights reserved.                           .
.                                                                             .
.    Technologies used in this source code are patented or patent pending     .
.    by Scalado AB Swedish Org. Number, 556594-6885.                          .
.                                                                             .
.    All Intellectual Property Rights related to this source code,            .
.    belongs to Scalado AB.                                                   .
.                                                                             .
.    This source code is furnished under license agreement and may be used    .
.    or copied only in accordance with terms of such license agreement.       .
.                                                                             .
.    Except as permitted by such license agreement, no part of this source    .
.    code may be reproduced, stored in a retrieval system, or transmitted,    .
.    in any form or by any means, electronic, mechanical, recording, or       .
.    otherwise, without the prior written permission of Scalado.              .
.                                                                             .
.    Scalado assumes no responsibility or liability for any errors or         .
.    inaccuracies in this source code or any consequential, incidental or     .
.    indirect damage arising out of the use of this source code.              .
.                                                                             .
.    Scalado and the Scalado logo are either registered trademarks or         .
.    trademarks of Scalado AB in Sweden and/or other countries.               .
.                                                                             .
. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .*/

#ifndef FM_AUTORAMA_H
#define FM_AUTORAMA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "caps_base.h"
#include "scbdefs.h"

//=============================================================================
/**
    @ingroup g_fm_autorama
    @file fm_autorama.h
    @brief Defines the interface of the Caps Feature Module: @a AutoRama
*/
//=============================================================================
/**
    @addtogroup g_fm_autorama
    @brief Panorama creation from multple images.

    @{
        @defgroup fxgroup_autoramatransform PanoramaTransform
        @defgroup fxgroup_panoramalens Lens
        @defgroup fxgroup_stitch Stitch
        @defgroup fxgroup_vftracker VFTracker
        @defgroup fm_autorama_util AutoRamaUtil
*/
//-----------------------------------------------------------------------------

/**
    @brief Object encapsulating the geometric transform of an image.
    @ingroup fxgroup_autoramatransform
*/
typedef struct sPanoramaTransform PanoramaTransform;

/**
    @brief Main object for stitching images
    @ingroup fxgroup_stitch
*/
typedef struct sPanoramaEngine PanoramaEngine;

/**
    @brief ViewFinder Tracker. Motion tracking with the viewfinder.
    @ingroup fxgroup_vftracker
*/
typedef struct sVFTracker VFTracker;


/**
    @brief Defines the viewfinder tracker type.
    @ingroup fxgroup_vftracker
*/
typedef enum CTVfTrackerType
{
    /**
        @brief Tracks movement in center region of viewfinder.
    */
    CTVFTRACKERTYPE_FAST = 0,
    /**
        @brief Tracks movement in multiple regions of viewfinder.
    */
    CTVFTRACKERTYPE_MULTIREGION = 1,
    /**
    @brief Tracks movement in the corners of the image. Used for background tracking.
    */
    CTVFTRACKERTYPE_SIDES = 2
}CTVfTrackerType;

/**
    @brief
    Defines the panorama mode, i.e. if the panorama is horizontal, vertical etc.
*/
typedef enum ePanoramaDirection
{
    /**
        @brief Unknown direction.
    */
    PANORAMA_DIRECTION_UNKNOWN  = 0,

    /**
        @brief Horizontal panorama where the last image in the series 
        is the rightmost image.
    */
    PANORAMA_DIRECTION_RIGHT  = 1,

    /**
        @brief Horizontal panorama where the last image in the series 
        is the leftmost image.
    */
    PANORAMA_DIRECTION_LEFT = 2,

    /**
        @brief Vertical panorama, last image most upwards.
    */
    PANORAMA_DIRECTION_UP    = 3,

    /**
        @brief Vertical panorama, last image most downwards
    */
    PANORAMA_DIRECTION_DOWN    = 4
} PanoramaDirection;


#define PANORAMA_BLEND_MODE_MASK 0x0F

/**
    @brief
    Defines the way the panorama images are blended.
*/
typedef enum PanoramaBlendMode
{
    /**
        @brief Simple blending using a linear blend between images.
    */
    PANORAMA_BLEND_MODE_LINEAR = 1,

    /**
        @brief More advanced blending using several frequency bands.

        This mode requires more memory and is more computationally heavy.
        Only supported in the directions PANORAMA_DIRECTION_RIGHT and
        PANORAMA_DIRECTION_LEFT. For those directions, this is the default
        value, as of Caps 3.7 .
    */
    PANORAMA_BLEND_MODE_MULTILEVEL_NORMAL = 2,

    /**
        @brief Similar to PANORAMA_BLEND_MODE_MULTILEVEL_NORMAL,
        but more memory needed.

        In some cases better quality than
        PANORAMA_BLEND_MODE_MULTILEVEL_NORMAL. Only supported in the directions
        PANORAMA_DIRECTION_RIGHT and PANORAMA_DIRECTION_LEFT.
    */
    PANORAMA_BLEND_MODE_MULTILEVEL_HIGH = 3,

    /**
        @brief Similar to PANORAMA_BLEND_MODE_MULTILEVEL_HIGH.

        This mode uses the most amount of memory, and requires the largest
        amount of CPU power. Only supported in the directions
        PANORAMA_DIRECTION_RIGHT and PANORAMA_DIRECTION_LEFT.
    */
    PANORAMA_BLEND_MODE_MULTILEVEL_BEST = 4,
    /** No path optimization only a straight line. Used for stereoscopic 
    panorama and only valid for 
    PANORAMA_DIRECTION_RIGHT and PANORAMA_DIRECTION_LEFT. */
    PANORAMA_BLEND_MODE_STEREO = 5


} PanoramaBlendMode;

/**
    @brief
    Defines color and intensity compensation options for panorama generation.
*/
typedef enum PanoramaBlendModeOpt
{
    /**
        @brief Turn off intensity compensation.

        Additional blending option, combine with one of the blend modes and
        optionally with PANORAMA_BLEND_MODE_OPT_NO_COLOR_COMP as well. Per
        default, the images' intensities are normalized, which results in
        smooth panoramas even with different exposure settings for each image
        in the series. If the intensity affecting exposure settings are known
        to be the same for all images, turn off the intensity compensation using
        this option.
     */
    PANORAMA_BLEND_MODE_OPT_NO_INTENSITY_COMP = 16,

    /**
        @brief Turn off color compensation.

        Additional blending option, combine with one of the blend modes and
        optionally with PANORAMA_BLEND_MODE_OPT_NO_INTENSITY_COMP as well.
        Per default, the images' colors are normalized, which results in smooth
        panoramas even with different white balance settings for each image in the
        series. If the exposure settings that affect the color tone of the images
        are known to be the same for all images, turn off the color compensation
        using this option.
    */
    PANORAMA_BLEND_MODE_OPT_NO_COLOR_COMP = 32
} PanoramaBlendModeOpt;

/**
    @brief Default overlap in percent.

    @sa caps_panoramaTransformIsTimeToCapture()
*/
#define PANORAMA_DEFAULT_OVERLAP 45

/**

    @brief Default minimum value for caps_panoramaTransformGetDirection() in percent.

	@sa caps_panoramaTransformGetDirection()
*/
#define PANORAMA_DEFAULT_DIRECTION_TRIGGER 10

//-----------------------------------------------------------------------------
/**
    @addtogroup fxgroup_autoramatransform
    @brief Utility functions for handling the result of the viewfinder tracking.

    The PanoramaTransform interface contains help functions for handling
    the result of the viewfinder tracking. It contains getters for the
    PanoramaTransform class and some help functions to improve viewfinder
    tracking logic and visualization.

    @{
*/
// NOTE! page 'page_panorama_transform_usage' is included from separate document:
//  "...\fm_autorama\doc\fm_autorama.doxygen"
/**
    @brief
    Create a panorama transform object. The object must be destroyed by caps_panoramaTransformDestroy().

    @param[out] ppPanoramaTransform
    The created object.

    @return
    @c CERR_OK or a specific error code
    
    @since 3.3
*/
SCBIMPORT CRESULT caps_panoramaTransformCreate( PanoramaTransform** ppPanoramaTransform );

/**
    @brief
    Destroy a panorama transform object

    @param pPanoramaTransform
    The object to destroy.
    
    @since 3.3
*/
SCBIMPORT void  caps_panoramaTransformDestroy( PanoramaTransform* pPanoramaTransform );

/**
    @brief
    Initialize a panorama transform object with desired translation values

    @param[in,out] pTransform
    the object that will be changed

    @param pDxDy delta x and delta y represented by the transform.

    @param pDims image dimensions for the transform

    @return
    @c CERR_OK or a specific error code

    @since 3.3
*/
SCBIMPORT CRESULT caps_panoramaTransformSetTranslation( PanoramaTransform* pTransform, CTVector* pDxDy, CTSize* pDims);

/**
    @brief
    Get the translation part of a PanoramaTransform

    @param pTransform
    an image transform

    @param[out] pDxDy 
    delta x and delta y represented by the transform.

    @param[out] pDims 
    image dimensions for the transform

    @since 3.3
*/
SCBIMPORT void caps_panoramaTransformGetTranslation( PanoramaTransform* pTransform, CTVector* pDxDy, CTSize* pDims);

/**
    @brief Get the main direction of a PanoramaTransform

    The PanoramaDirection of a panorama could
    either be determined automatically or be set by the application.
    This function could be used together with viewfinder tracking
    to determine the direction automatically. This is a very simple function
    that simply checks if the translation is above the given threshold in any
    direction.

    @param pTransform 
    Usually a transform created by a VFTracker.

    @param[out] pDirection 
    direction of the panorama.

    @param minimumDelta 
    Minimum translation in percent. if the translation in pTransform is smaller
    than this value, the function returns false.
    A recommended value is PANORAMA_DEFAULT_DIRECTION_TRIGGER.

    @return
    true if a direction could be determined. false if a direction could not be determined from the transform.

    @since 3.3
*/
SCBIMPORT CTbool caps_panoramaTransformGetDirection( PanoramaTransform* pTransform,
                                          PanoramaDirection* pDirection,
                                          CTint32 minimumDelta);

/**
    @brief Determines from a PanoramaTransform if it is time to capture a new image.

    This is a very simple help function, that simply checks if the translation
    of the transform is larger than the overlap value suggests, in the given
    direction of the panorama.

    @param pTransform 
    Description of the transform between two images

    @param direction 
    The type of panorama being created

    @param overlap 
    Desired overlap in the panorama image series in percent.
    100 means the images overlap totally. 0 means no overlap.
    must be in range [10 90]. A recommended value is PANORAMA_DEFAULT_OVERLAP.

    @return 
    true if it is time to capture a new image, false otherwise.

    @since 3.3
*/
SCBIMPORT CTbool caps_panoramaTransformIsTimeToCapture( PanoramaTransform* pTransform,
                                             PanoramaDirection direction,
                                             CTint32 overlap);

/**
    @}
*/ // end 'Autoramatransform'

//-----------------------------------------------------------------------------
/** 
    @addtogroup fxgroup_panoramalens
    @brief Lens parameters

    The camera model describes the physical properties of the camera,
    for example focal length and distortion. For more info see
    @ref page_camera_calibration

    @{
*/
//-----------------------------------------------------------------------------
/** 
    @defgroup fxgroup_panoramalens_cameracalibration Camera calibration
    @brief How to determine the lens parameter settings
*/
// NOTE! page 'pageCameraCalibration' is included from separate document:
//  "...\fm_autorama\doc\fm_autorama.doxygen"
//-----------------------------------------------------------------------------

/**
	@brief Lens parameters defining the camera lens
    
    The lens is valid for images of any size,
    not only the calibration image size iWidth and iHeight.
    The images that the PanoramaLens is used on should however
    have the same aspect ratio as the calibration image size.
    
    Example lens:\n
    @code
    const PanoramaLens lensExample = 
    {
        { 665.0f, 665.0f},
        { 320.0f, 240.0f},
        0.0f,
        { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
        640, 480
    };
    @endcode
*/
typedef struct PanoramaLens
{
    /**
        @brief Focal length in pixel coordinates

        If the pixels are square shaped, the x- and y-part of the @c afFocalLength are the same.

        Comparing to @ref CameraCalibrationMatlab "[1]"; @c afFocalLength = fc
    */
    CTfloat afFocalLength[2];

    /**
        @brief The coordinates of the principal point in pixel coordinates.

        The coordinate convention of the image plane pixel coordinates are that
        the top left corner of the image is (0,0) and the bottom right corner is
        (iWidth-1, iHeight-1). Typically the principal point is very close or
        identical to the coordinates of the midpoint of the image.

        Comparing to @ref CameraCalibrationMatlab "[1]" , @c afPrincipalPoint = cc
    */
    CTfloat afPrincipalPoint[2];

    /**
        @brief Skew coefficient.

        0 means no skew. This is only used if the camera sensor is a non rectangular 
        parallellogram. For a more detailed description, see @ref CameraCalibrationMatlab "[1]".

        Comparing to @ref CameraCalibrationMatlab "[1]", @c fSkew = alpha_c
    */
    CTfloat fSkew;

    /**
        @brief Distortion coefficients.

        These parameters describe the distortion as a function of the distance to 
        the principal point of the image, the radius.

        @c afDist[0], @c afDist[1], @c afDist[4] defines the second, fourth and
        sixth order radial distortion, and
        @n
        @c afDist[2], @c afDist[3] defines the tangential distortion.

        Comparing to @ref CameraCalibrationMatlab "[1]", @c afDist[0] = kc[1], ... , @c afDist[4] = kc[5].
        @n
        Comparing to @ref CameraCalibrationOpenCV "[2]", @c afDist[0] = k1 ,
        @c afDist[1] = k2, @c afDist[4] = 0. @c afDist[2] = p1, @c afDist[3] = p2
    */
    CTfloat afDist[5];

    /**
        @brief Image width in pixels when the camera was calibrated.
    */
    CTuint32 iWidth; 
    
    /**
        @brief Image height in pixels when the camera was calibrated.
    */
    CTuint32 iHeight;
} PanoramaLens;

/**
    @}
*/ // end 'Lens'

//-----------------------------------------------------------------------------

/** 
    @addtogroup fxgroup_stitch
    @brief The Stitch interface contains functions for the last step in the
    panorama creation process, stitching images.

    @{
*/
//------------------------------------------------------------------------------

/**
    @brief 
    Create a PanoramaEngine object.

    @param ppPanEng 
    The created object

    @param pLens 
    Lens parameters of the camera taking images for the panorama.\n\n
    There is no closed expression for the range of the PanoramaLens members.
    This is not possible due to the complexity of the usage of the lens.
    Some extreme lens parameter values may result in returning
    @c CERR_INVALID_PARAMETER

    @param imSize 
    Size of the individual images in the image series

    @param direction 
    The direction of the panorama.
    @c PANORAMA_DIRECTION_UNKNOWN is not allowed.

    @return 
    CERR_OK or an error otherwise

    @sa caps_panoramaDestroy

    @sa caps_vftrackerRegisterImage

    @since 3.3
*/
SCBIMPORT CRESULT caps_panoramaCreate( PanoramaEngine** ppPanEng, 
                             const PanoramaLens* pLens, 
                             CTSize imSize, 
                             PanoramaDirection direction );

/**
    @brief 
    Destroy a PanoramaEngine object.

    @param pPanEng 
    The object to destroy.

    @sa caps_panoramaCreate

    @since 3.3
*/
SCBIMPORT void caps_panoramaDestroy( PanoramaEngine* pPanEng);


/**
    @brief
    Set the blend mode of the panorama creation, choosing one of several algorithms
    to be used for blending images to a panorama.

    @param pPanEng The panorama object
    @param blendMode The algorithm to use. The value should be
    one of ::PanoramaBlendMode values and optionally | (or) with one or more
    ::PanoramaBlendModeOpt. Some algorithms are not supported for all
    modes of the panorama objects (see ::PanoramaBlendMode). For example, to set
    multilevel high, without color compensation but with intensity compensation,
    the value should be:
    @n@n
    PANORAMA_BLEND_MODE_MULTILEVEL_HIGH | PANORAMA_BLEND_MODE_OPT_NO_COLOR_COMP.
    @n@n
    If a non supported mode is encountered, CERR_INVALID_PARAMETER is returned.

    @sa PanoramaBlendMode and PanoramaBlendModeOpt

    @return CERR_OK or CERR_INVALID_PARAMETER.

    @since 3.6
*/
SCBIMPORT CRESULT caps_panoramaSetBlendMode( PanoramaEngine* pPanEng, CTuint32 blendMode);

/**
    @brief 
    Add an image to the panorama creation in progress.

    @param pPanEng 
    The PanoramaEngine object.

    @param pJpegImage 
    Jpeg image in memory. This image is at all times owned by the caller and
    must be kept alive during both the lifetime of pPanEng and during the
    lifetime of any CTSession that has been created by the pPanEng object.

    @param pTransform The approximate transform between the added image,
    and the previous one (if any). May be @c NULL if the added image is the
    first in a set.

    @return 
    CERR_OK or an appropriate error code.
    CERR_PANORAMA_TRANSFORM is returned if the transform does not match the
    direction of the panorama, or if the transform suggests no overlap to the
    previously added image.

    @remark
    Internally this function does not perform any heavy computations.
    It is guaranteed to return quickly.

    @sa caps_panoramaAddImageRaw
    @sa caps_panoramaAddImageJpegFile

    @since 3.3
*/
SCBIMPORT CRESULT caps_panoramaAddImageJpegBuffer( PanoramaEngine* pPanEng, const CTBuffer* pJpegImage, PanoramaTransform* pTransform );

/**
    @brief 
    Add an image to the panorama creation in progress.

    @param pPanEng 
    The PanoramaEngine object.

    @param filename
    Jpeg image on file system.

    @param enablePrefetch
    Sets the prefetching option for the JPEG decoder.
    When disabling the prefetch option, the jpeg file will not be read into
    memory. Therefore the memory needed in the session will be reduced with approx.
    the JPEG file size. True, if Jpeg files should be read into memory. False, otherwise.

    @param pTransform The approximate transform between the added image,
    and the previous one (if any). May be @c NULL if the added image is the
    first in a set.

    @return 
    CERR_OK or an appropriate error code.
    CERR_PANORAMA_TRANSFORM is returned if the transform does not match the
    direction of the panorama, or if the transform suggests no overlap to the
    previously added image.

    @sa caps_panoramaAddImageRaw
    @sa caps_panoramaAddImageJpegBuffer

    @since 3.6
*/
SCBIMPORT CRESULT caps_panoramaAddImageJpegFile( PanoramaEngine* pPanEng,
                                      const DCHAR* filename,
                                      CTbool enablePrefetch,
                                      PanoramaTransform* pTransform );

/**
    @brief 
    Add an image to the panorama creation in progress.

    @param pPanEng 
    The PanoramaEngine object.

    @param pImage 
    Raw image in memory. This image is at all times owned by the caller and
    must be kept during both the lifetime of pPanEng and during the lifetime of any session
    that pPanEng may have created by caps_newSessionWithPanorama.

    @param pTransform The approximate transform between the added image,
    and the previous one (if any). May be @c NULL if the added image is the
    first in a set.

    @return 
    CERR_OK or an appropriate error code.
    CERR_PANORAMA_TRANSFORM is returned if the transform does not match the
    direction of the panorama, or if the transform suggests no overlap to the
    previously added image.

    @remark 
    Internally this function does not perform any heavy computations.
    It is guaranteed to return quickly.

    @sa caps_panoramaAddImageJpegBuffer

    @since 3.3
*/
SCBIMPORT CRESULT caps_panoramaAddImageRaw( PanoramaEngine* pPanEng, CTImage* pImage, PanoramaTransform* pTransform );

/**
    @brief
    Add an image to the panorama creation in progress.

    @param pPanEng
    The PanoramaEngine object.

    @param pBitmap
    Raw image in memory. This image is at all times owned by the caller and
    must be kept during both the lifetime of pPanEng and during the lifetime of any session
    that pPanEng may have created by caps_newSessionWithPanorama.

    @param pTransform The approximate transform between the added image,
    and the previous one (if any). May be @c NULL if the added image is the
    first in a set.

    @return
    CERR_OK or an appropriate error code.
    CERR_PANORAMA_TRANSFORM is returned if the transform does not match the
    direction of the panorama, or if the transform suggests no overlap to the
    previously added image.

    @remark
    Internally this function does not perform any heavy computations.
    It is guaranteed to return quickly.

    @sa caps_panoramaAddImageRaw

    @since 5.3
*/
SCBIMPORT CRESULT caps_panoramaAddImageBitmap( PanoramaEngine* pPanEng, CTBitmap* pBitmap, PanoramaTransform* pTransform );

/**
@brief 
Add an image through a region decoder to the panorama creation in progress.

@param pPanEng 
The PanoramaEngine object.

@param pDecoder 
A region decoder. This is at all times owned by the caller and
must be kept during both the lifetime of pPanEng and during the lifetime of any session
that pPanEng may have created by caps_newSessionWithPanorama.

@param pTransform The approximate transform between the added image,
and the previous one (if any). May be @c NULL if the added image is the
first in a set.

@return 
CERR_OK or an appropriate error code.
CERR_PANORAMA_TRANSFORM is returned if the transform does not match the
direction of the panorama, or if the transform suggests no overlap to the
previously added image.

@remark 
Internally this function does not perform any heavy computations.
It is guaranteed to return quickly.

@sa caps_panoramaAddImageJpegBuffer

@since 5.1
*/
SCBIMPORT CRESULT caps_panoramaAddImageDecoder( PanoramaEngine* pPanEng,
                                                CTRegionDec* pDecoder,
                                                PanoramaTransform* pTransform );

/**
    @brief 
    Initiates a new session using a PanoramaEngine.

    @param pPanEng 
    The PanoramaEngine object.

    @param[out] session
    Pointer to a handle which will receive the constructed session. If 
    construction fails this argument is ignored.

    @remarks
    There must be at least two images added to the panorama before this function is called.
    The session is independent of the PanoramaEngine, i.e. pPanEng may be destroyed after this 
    function is called. However, the source images in the panorama, must be kept during
    the lifetime of the session.\n
    \n
    The processing time of this function is in the order of seconds.
    \n
    Note that the following regular CAPS functions are illegal to call after creating
    a session with this function:
    - caps_setSourceImageFile()
    - caps_setSourceImageBuffer()
    - caps_setSourceImageRaw()
    - caps_setSourceColor()
    - caps_setBackgroundColor()
    .

    @return 
    CERR_OK if successful or a specific error code upon failure.
    CERR_PANORAMA_LENS is returned if the lens is incorrect.
    CERR_PANORAMA_GEOMETRY is returned if the input-images could not
    be aligned to form a panorama

    @since 3.3
*/
SCBIMPORT CRESULT caps_newSessionWithExternalPanorama( PanoramaEngine* pPanEng, CTSession* session );

//------------------------------------------------------------------------------

/**
    @brief 
    Initiates a new session using a PanoramaEngine.

    @param pPanEng 
    The PanoramaEngine object.

    @param[out] ppIterator
    An iterator object.
    - Iterate on the object using caps_doNextIteration().
    - When the last iteration is successful, retrieve the CTSession using
      caps_getIterationData(), by converting the CTuint32 to a CTSession.
    - When caps_getIterationData() is called, the ownership of the CTSession object is
      transferred to the caller.
    - caps_getIterationData() may only be called once on a CTIterator created by
      caps_newSessionWithExternalPanoramaIterative(). I.e. only one CTSession may be created
      for each call to caps_newSessionWithExternalPanoramaIterative().
    - Calling caps_getIterationData() before the last iteration
      is finished returns an error.
    .
    @n
    Only the following functions are valid for the iterator object:
    - caps_doNextIteration()
    - caps_estimateIterationCount()
    - caps_getCurIterationCount()
    - caps_getIterationData()
    - caps_destroyIterator()
    .

    @remarks
    - There must be at least two images added to the panorama before this function is called.
    - The session is independent of the PanoramaEngine, i.e. pPanEng may be destroyed after this 
      function is called. However, the source images in the panorama, must be kept during
      the lifetime of the session.
    .
    @n
    The processing time of this function is in the order of seconds.
    @n
    Note that the following regular CAPS functions are illegal to call after creating
    a session with this function:
    
    @li caps_setSourceImageFile()
    @li caps_setSourceImageBuffer()
    @li caps_setSourceImageRaw()
    @li caps_setSourceColor()
    @li caps_setBackgroundColor()

    @return 
    CERR_OK if successful or a specific error code upon failure.

    @since 3.6
*/
SCBIMPORT CRESULT caps_newSessionWithExternalPanoramaIterative(
    PanoramaEngine* pPanEng, CTIterator** ppIterator );

/**
    @}
*/ // end 'Stitch'

//-----------------------------------------------------------------------------
/** 
    @addtogroup fxgroup_vftracker
    @brief Viewfinder image tracking

    The VFTracker is an interface for tracking the movement of a camera using
    viewfinder images. It could be used in many kinds of applications but is
    especially suited for Panorama image creation.

    @{
*/
//-----------------------------------------------------------------------------

/**
    @brief
    Create a VFTracker object to be used when registering images with
    caps_vftrackerRegisterImage()

    @param ppVFTracker 
    The created object

    @param viewfinderSize 
    Size of viewfinder images

    @return 
    CERR_OK or an error otherwise

    @sa caps_vftrackerDestroy()
    @sa caps_vftrackerRegisterImage()

    @since 3.3
*/
SCBIMPORT CRESULT caps_vftrackerCreate( VFTracker** ppVFTracker, CTSize viewfinderSize);

/**
    @brief
    Create a VFTracker object 

    @param ppVFTracker 
    The created object

    @param viewfinderSize 
    Size of viewfinder images

    @param type
    Type of vftracker

    @return 
    CERR_OK or an error otherwise

    @sa caps_vftrackerDestroy()

    @since 3.9.5
*/
SCBIMPORT CRESULT caps_vftrackerCreateEx( VFTracker** ppVFTracker, CTSize viewfinderSize, CTVfTrackerType type);

/**
    @brief
    Destroy a VFTracker object.

    @param pVFTracker 
    The object to destroy.

    @sa caps_vftrackerCreate()

    @since 3.3
*/
SCBIMPORT void caps_vftrackerDestroy( VFTracker* pVFTracker);

/**
    @brief
    Performs overlapping calculations from viewfinder image.

    Pass all viewfinder images to this function
    to find out when its time to capture a new image.

    @param pVFTracker 
    The VFTracker object.

    @param pViewFinderImage 
    The image from the viewfinder.
    
    @param[out] pTransform 
    Accumulated delta since viewfinder was created or caps_vftrackerStartOver() was called.
    The previous values of the transform object are ignored.

    @return 
    CERR_OK or an appropriate error code

    @sa caps_vftrackerStartOver()

    @since 3.3
*/
SCBIMPORT CRESULT caps_vftrackerRegisterImage( VFTracker* pVFTracker,
                                               CTImage* pViewFinderImage,
                                               PanoramaTransform* pTransform );

/**
    @brief
    Resets the transform return by caps_vftrackerRegisterImage().
    
    Resets the PanoramaTransform (accumulated x/y-delta) returned by
    caps_vftrackerRegisterImage() to [0,0].

    @since 3.3
*/
SCBIMPORT void caps_vftrackerStartOver( VFTracker* pVFTracker);

/**
    @brief
    Find best match of a template in an image by 2D correlation.

    The template T is sliding over the image I, creating a resulting
    image R. The analysis is performed with a multiscale method.
    In general the matching quality is not affected by the use of different scales.
    However, in some cases the result is different from, not necessarily worse than,
    using caps_matchTemplate().

    @param pImage
    Image, must have format CM_GRAY8.

    @param pTemplate
    Image template, must have format CM_GRAY8

    @param[out] pPos
    Position for best match. (0,0) means that the best match for the
    template is in the upper left corner of the image.

    @param[out] ppImageOut
    (OPTIONAL) May be NULL. The result of the matching.
    Color format is CM_UNKNOWN. Format is 32 bit signed integer.
    This image is primarily intended for development purposes.

    @return
    @c CERR_OK or a specific error code

    @sa
    caps_matchTemplate()

    @since 5.1
*/
SCBIMPORT CRESULT caps_matchTemplateWithPyramid(CTImage* pImage,
                                                CTImage* pTemplate,
                                                CTVector* pPos,
                                                CTImage** ppImageOut);

/**
    @brief
    Find best match of a template in an image by 2D correlation.

    This function is very slow and should only be performed on
    very small images, i.e. 100x100, 50x50.
    The template T is sliding over the image I, creating a resulting
    image R.

    @param pImage
    Image, must have format CM_GRAY8.

    @param pTemplate
    Image template, must have format CM_GRAY8

    @param pImageRect
    Area of pImage to use. Must fit within pImage.

    @param pTemplateRect
    Area of pTemplate to use. Must fit within pTemplate. Width and height must
    be less than or equal to those of pImageRect.

    @param[out] pPos
    Position for best match. (0,0) means that the best match for the
    template is in the upper left corner of the image.

    @param[out] ppImageOut
    (OPTIONAL) May be NULL. The result of the matching.
    The size of this image is
    (pImageRect.w - pTemplateRect.w + 1) x (pImageRect.h - pTemplateRect.h + 1).
    Color format is CM_UNKNOWN. Format is 32 bit signed integer.
    This image is primarily intended for development purposes.

    @return
    @c CERR_OK or a specific error code

    @sa
    caps_matchTemplateWithPyramid()

    @since 5.1
*/
SCBIMPORT CRESULT caps_matchTemplate(CTImage* pImage,
                                     CTImage* pTemplate,
                                     CTRect* pImageRect,
                                     CTRect* pTemplateRect,
                                     CTVector* pPos,
                                     CTImage** ppImageOut);

/**
    @}
*/ // end 'VFTracker'
//-----------------------------------------------------------------------------

/**
    @}
*/ // end 'fm_autorama'
//-----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif // FM_AUTORAMA_H
