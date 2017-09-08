/*  . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
.                                                                             .
.    (c) 2000-2011 Scalado AB. All rights reserved.                           .
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

#ifndef FM_LOCALTIMEWARP_H
#define FM_LOCALTIMEWARP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "scbdefs.h"
#include "ctdecoder.h"
#include "caps_types.h"

//=============================================================================
/**
    @file fm_localtimewarp.h
    @brief API for blending different parts of images from an image series into
    a composite image.
    @ingroup fm_localtimewarp
*/
//=============================================================================

/**
    @addtogroup fm_localtimewarp
    @brief API for blending different parts of images from an image series into
    a composite image.

    @par Setup
    To initiate a LocalTimeWarp session, specify a set of source images,
    and select a background:
    @n@n
    - ctlocaltimewarp_create()
    - ctlocaltimewarp_addSource() - For each source image.
    - ctlocaltimewarp_setBackgroundSource()
    .
    @n
    After this, an internal canvas has been created which acts as the workspace
    holding the resulting image.

    @par Basic workflow
    To overlay an image area from one of the added source images, and render
    the result:
    @n@n
    -# ctlocaltimewarp_setReplaceArea()
    -# ctlocaltimewarp_setReplaceSource()
    -# ctlocaltimewarp_update() - Calling update will modify the canvas with the given area and source.
    -# caps_render*() &nbsp; &nbsp; * = any CAPS render function.
    .

    @par Render to output
    In order to render the current canvas, a session must first be created, given
    a decoder that provides the result image data. This decoder is obtained from
    the @c CTLocalTimeWarp object:
    @n@n
    - ctlocaltimewarp_getDecoder()
    - caps_createSessionFromDecoder()
    - caps_render*() &nbsp; &nbsp; * = any CAPS render function; e.g. caps_renderAsRawToBuffer()
    .

    @par Switching source overlays
    Typically an application should allow a user to interactively browse between
    all source images for the currently set replace region, and display the
    results on screen.
    @n@n
    This involves repeating steps: 1-4 above (in @em "Basic workflow"), which
    will replace the selected area and source, and update the canvas.
    @n@n
    <b>Note</b> that whenever ctlocaltimewarp_update() is called, after a new
    replacement area/source has been set, the image data provided by the decoder
    will have changed. If the same (output) CTSession is used for subsequent
    rendering operations, the session must be notified about the update before
    the actual render call is made. This is done with:
    @n@n
    caps_signalSessionEvent( outputSession, EVENT_SOURCEDATA_CHANGE );
    @n@n
    The output session also needs to notified (with the above call) after either
    of the following functions have been invoked:
    - ctlocaltimewarp_discard()
    - ctlocaltimewarp_setBackgroundSource()
    .

    @par Commiting and discarding changes
    To fixate the current overlay onto the canvas, call:
    @n@n
    - ctlocaltimewarp_commit()
    .
    @n
    At this point, the canvas change cannot be undone. The current canvas will now be used
    as the background for subsequent operations.
    @n@n
    To restore the canvas to the state it had immediately after the last call to commit, call
    @n@n
    - ctlocaltimewarp_discard()
    .
    @n
    Note that if update is called immediately after discard, the most recently set area and source
    will be reapplied to the canvas.

    @par Example
    @ref fm_localtimewarp_example

    @{
*/

/**
    @brief
    The central handle type used for Local TimeWarp

    @since 3.10
*/
typedef struct CTLocalTimeWarp CTLocalTimeWarp;

/**
    @brief
    Quality settings.
*/
typedef enum CTLTW_PRIORITY
{
    CTLTW_PRIO_QUALITY, ///< Quality
    CTLTW_PRIO_SPEED   ///< Speed
} CTLTW_PRIORITY;

/**
    @brief Creates a Local TimeWarp session.

    @param[out] ppLocalTimeWarp Created Local TimeWarp session.

    @return @c CERR_OK or a suitable error code.

    @since 3.10
*/
SCBIMPORT CRESULT ctlocaltimewarp_create( CTLocalTimeWarp **ppLocalTimeWarp );

/**
    @brief Destroys and frees memory allocated inside the given Local TimeWarp instance.

    Any decoders that have been extracted, using ctlocaltimewarp_getDecoder(), cannot be used after the Local TimeWarp instance has been destroyed.

    Source sessions and extracted decoders will not be destroyed, but must be deallocated by the caller.

    @param pLocalTimeWarp The Local TimeWarp instance to destroy.

    @since 3.10
*/
SCBIMPORT void ctlocaltimewarp_destroy( CTLocalTimeWarp *pLocalTimeWarp );

/**
    @brief Adds a source image provided via a CTSession object

    @note
    All sources must have the same dimensions.

    @param pLocalTimeWarp The Local TimeWarp instance to which the session will be added.
    @param session The session to be added.

    @return @c CERR_OK or a suitable error code.

    @since 3.10
*/
SCBIMPORT CRESULT ctlocaltimewarp_addSource( CTLocalTimeWarp *pLocalTimeWarp, CTSession session );

/**
    @brief Gets the number of added sources to the given Local TimeWarp instance.

    @param pLocalTimeWarp The Local TimeWarp instance.

    @return The number of added sources. If an invalid instance is used zero will be returned.

    @since 3.10
*/
SCBIMPORT CTuint32 ctlocaltimewarp_getNumberOfSources( CTLocalTimeWarp *pLocalTimeWarp );

/**
    @brief Sets which of the added sources to use as the background.

    Renders the background source to the internal canvas, discarding any previous
    operations on the canvas.

    @note
    After a call to this function, the session that is used to render the result
    should be notified that the underlying image data has changed, by calling
    caps_signalSessionEvent() with the value ::EVENT_SOURCEDATA_CHANGE
    as the second argument.

    @param pLocalTimeWarp The Local TimeWarp instance in which to set the background.
    @param sourceNumber The index of the source to be used as background.
    @param[out] ppIterator An optional pointer to an iterator object.
    The returned iterator must be completed before any other call to this Local TimeWarp
    instance is made.
    If @c NULL is passed, the operation will be fully completed before the function returns.

    @return @c CERR_OK or a suitable error code.

    @see
    - caps_doNextIteration()
    - @ref caps_iterators
    - ctlocaltimewarp_getDecoder()
    .

    @since 3.10
*/
SCBIMPORT CRESULT ctlocaltimewarp_setBackgroundSource( CTLocalTimeWarp *pLocalTimeWarp,
                                                       CTuint32 sourceNumber,
                                                       CTIterator **ppIterator );

/**
    @brief Sets the area to be replaced by the next call to ctlocaltimewarp_update(). 

    The area will be replaced as cleanly as possible, trying to minimize
    visual traces of the blending.

    This function does not modify the internal canvas.

    @param pLocalTimeWarp The Local TimeWarp instance in which to set the replace area.

    @param pInnerRect The rectangle describing the inner area to be replaced. Note that objects that change in between 
    images, such as faces, should be contained within the rectangle for best result. Width and height must be >= 2.
    @param feathering The maximum distance outside the inner rectangle the algorithm is allowed to modify.
    The boundary between the blended images will be between the inner rectangle and outwards feathering pixels.
    @param maxTranslation Describes the maximum image-to-image translation the algorithm should account for when 
    performing registration. Appropriate values for this depends on how much, in pixels,
    the images are expected to be translated. This is highly application dependent and depends on for example
    the time difference between the sources, camera movement, image resolution.

    @return @c CERR_OK or a suitable error code.

    @since 3.10
*/
SCBIMPORT CRESULT ctlocaltimewarp_setReplaceArea( CTLocalTimeWarp *pLocalTimeWarp,
                                                  CTRect *pInnerRect,
                                                  CTuint32 feathering,
                                                  CTuint32 maxTranslation );

/**
    @brief Sets which source the inserted image area is to be fetched from.

    This function does not modify the internal canvas.

    @param pLocalTimeWarp The Local TimeWarp instance in which to set the replace source.
    @param sourceNumber The number of the source to be used to replace the image region in the background image.

    @return @c CERR_OK or a suitable error code.

    @since 3.10
*/
SCBIMPORT CRESULT ctlocaltimewarp_setReplaceSource( CTLocalTimeWarp *pLocalTimeWarp,
                                                    CTuint32 sourceNumber );

/**
    @brief Sets what the algorithm should prioritize.

    Available settings for @c CTLTW_PRIORITY are:
    - @c CTLTW_PRIO_QUALITY - (default) At this setting the algorithm does not compromise quality at any cost. 
    - @c CTLTW_PRIO_SPEED   - At this setting the algorithm tries to save time by reducing accuracy of some
                              internal solution steps. This setting increases the risk of erroneous results but can in many cases generate comparable results as @c CTLTW_PRIO_QUALITY.
    .

    @param pLocalTimeWarp The Local TimeWarp instance for which to change priority.
    @param priority The priority setting to use.

    @return @c CERR_OK or a suitable error code.

    @since 3.10
*/
SCBIMPORT CRESULT ctlocaltimewarp_setPriority( CTLocalTimeWarp *pLocalTimeWarp, CTLTW_PRIORITY priority );

/**
    @brief Renders to the internal canvas using the current settings.

    This function blends the image data, specifed via the most recent calls to
    ctlocaltimewarp_setReplaceArea() and ctlocaltimewarp_setReplaceSource(),
    onto the current background.

    The content of the current background is determined by the whichever
    of the following two functions was called last.
    - ctlocaltimewarp_setBackgroundSource()
    - ctlocaltimewarp_commit()
    .

    @note
    After a call to this function, the session that is used to render the result
    should be notified that the underlying image data has changed, by calling
    caps_signalSessionEvent() with the value ::EVENT_SOURCEDATA_CHANGE
    as the second argument.

    @param pLocalTimeWarp The Local TimeWarp instance to update.
    @param[out] ppIterator An optional pointer to an iterator object. The
    returned iterator must be completed before any other call to this Local TimeWarp
    instance is made.
    If @c NULL is passed, the operation will be fully completed before the function returns.

    @return @c CERR_OK or a suitable error code.

    @see
    - ctlocaltimewarp_commit()
    - caps_signalSessionEvent()
    - caps_doNextIteration()
    - @ref caps_iterators
    .

    @since 3.10
*/
SCBIMPORT CRESULT ctlocaltimewarp_update( CTLocalTimeWarp *pLocalTimeWarp,
                                          CTIterator **ppIterator );

/**
    @brief Commits a change to the internal canvas.

    This operation "freezes" the internal canvas, and makes its current state
    constitute the new background, onto which any subsequent update operations
    will be blended.

    @param pLocalTimeWarp The Local TimeWarp instance in which to commit the change.

    @return @c CERR_OK or a suitable error code.

    @since 3.10
*/
SCBIMPORT CRESULT ctlocaltimewarp_commit( CTLocalTimeWarp *pLocalTimeWarp );

/**
    @brief Restores the internal canvas to the state held at the time of the
    last call to ctlocaltimewarp_commit().

    @note
    After a call to this function, the session that is used to render the result
    should be notified that the underlying image data has changed, by calling
    caps_signalSessionEvent() with the value ::EVENT_SOURCEDATA_CHANGE
    as the second argument.

    @param pLocalTimeWarp The Local TimeWarp instance in which to discard the change.

    @return @c CERR_OK or a suitable error code.

    @since 3.10
*/
SCBIMPORT CRESULT ctlocaltimewarp_discard( CTLocalTimeWarp *pLocalTimeWarp );

/**
    @brief Gets a decoder which can be used to retrieve the internal canvas.

    From the decoder, a CTSession can be created with caps_createSessionFromDecoder(),
    which subsequently can be used to render the output.

    @param pLocalTimeWarp The Local TimeWarp instance. This object must not
    be destroyed while the decoder is in use.

    @param[out] ppDecoder The created decoder.
    Any number of decoders are allowed to be created from the same Local TimeWarp object.
    The decoder must be destroyed by the caller.

    @return @c CERR_OK or a suitable error code.

    @since 3.10
*/
SCBIMPORT CRESULT ctlocaltimewarp_getDecoder( CTLocalTimeWarp *pLocalTimeWarp, CTDecoder **ppDecoder );

//=============================================================================
/** @} */
// end addtogroup 'fm_localtimewarp'.


#ifdef __cplusplus
} // extern "C"
#endif


#endif // FM_LOCALTIMEWARP_H

