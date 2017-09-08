#ifndef ENGINE_OANEWFOAFEWN
#define ENGINE_OANEWFOAFEWN

#include "gesture.h"


namespace TouchlessA3D {

  /**
   * Can be used as argument when calling the function Engine#handleImage().
   */
  enum Rotate {
    /// No rotation.
		DO_NOT_ROTATE = 0,
    /// Rotate the input image 90 degrees clockwise before detecting objects in it.
		ROTATE_90 = 1,
    /// Rotate the input image 180 degrees before detecting objects in it.
		ROTATE_180 = 2,
    /// Rotate the input image 270 degrees clockwise before detecting objects in it.
		ROTATE_270 = 3
  };


  /**
   * This is the main interface for the Crunchfish %TouchlessA3D library.
   *
   * Create an instance, register gesture listeners, and then feed the engine
   * with images by calling handleImage().
   *
   * Copyright © 2013 Crunchfish AB. All rights reserved. All information herein
   * is or may be trade secrets of Crunchfish AB.
   */
  class TA3D_EXPORT Engine {
  public:
    class Private;

  private:
    Private *m_priv;

  public:
    /**
     * Constructs an Engine object. The Engine object cannot be used until
     * init() has been called on it.
     */
    Engine();
    ~Engine();

    /**
     * @brief Must be called before this Engine instance can be used.
     *
     * @param nInputImageWidth Width of images sent as input to handleImage().
     * @param nInputImageHeight Height of images sent as input to handleImage().
     * @param nInputImageStep Distance in bytes between the start of lines in
     * the input data sent to handleImage(). Must be a positive integer. If set
     * to zero, the value of nInputImageWidth is used instead.
     *
     * @return #TA3D_RESULT_OK if the operation was successful.<br>
     * #TA3D_RESULT_INVALID_INPUT if nInputImageWidth < 1 or nInputImageHeight < 1.<br>
     * #TA3D_RESULT_WRONG_INTERNAL_STATE if init() has already been called on this Engine instance.<br>
     * #TA3D_LICENSE_ERROR if the license key is not valid.<br>
     * #TA3D_LICENSE_CONNECTION_ERROR if not able to communicate with the license server.
     * #TA3D_OUT_OF_MEMORY if a memory allocation fails.
     */
    int init(int nInputImageWidth, int nInputImageHeight, int nInputImageStep = 0);

    /**
     * Sets a global parameter for this Engine instance.
     *
     * @see getParameter()
     *
     * @param nKey Identifies which parameter to set.
     * @param nValue Value to set for the specified paramter.
     *
     * @return #TA3D_RESULT_OK if the operation was successful.<br>
     * #TA3D_RESULT_INVALID_INPUT If nKey does not specify a valid parameter,
     * or if nValue is not valid for the specified parameter.
     */
    int setParameter(int nKey, int nValue);

    /**
     * Sets a global parameter for this Engine instance.
     *
     * @see getParameter()
     *
     * @param nKey Identifies which parameter to set.
     * @param fValue Value to set for the specified paramter.
     *
     * @return #TA3D_RESULT_OK if the operation was successful.<br>
     * #TA3D_RESULT_INVALID_INPUT If nKey does not specify a valid parameter,
     * or if fValue is not valid for the specified parameter.
     */
    int setParameter(int nKey, float fValue);

    /**
     * Gets the value for a global parameter for this Engine instance.
     *
     * @see setParameter()
     *
     * @param nKey Identifies which parameter to get the value for.
     * @param pnOutValue A pointer to the variable that will receive the value
     * of the parameter. Must not be zero.
     *
     * @return #TA3D_RESULT_OK if the operation was successful.<br>
     * #TA3D_RESULT_INVALID_INPUT If nKey does not specify a valid parameter,
     * or if pnOutValue is zero.
     */
    int getParameter(int nKey, int *pnOutValue);

    /**
     * Gets the value for a global parameter for this Engine instance.
     *
     * @see setParameter()
     *
     * @param nKey Identifies which parameter to get the value for.
     * @param pfOutValue A pointer to the variable that will receive the value
     * of the parameter. Must not be zero.
     *
     * @return #TA3D_RESULT_OK if the operation was successful.<br>
     * #TA3D_RESULT_INVALID_INPUT If nKey does not specify a valid parameter,
     * or if pfOutValue is zero.
     */
    int getParameter(int nKey, float *pfOutValue);

    /**
     * Registers a listener for a specific type of gesture.
     *
     * Callbacks to the listener will happen inside the call to handleImage().
     *
     * Example usage:
     *
     * @code
     * pEngine->registerGestureListener(OpenHandPresence::TYPE, pListener);
     * @endcode
     *
     * @see GestureListener#onGesture()
     * @see unregisterGestureListener()
     *
     * @param eType The type of gesture to listen for.
     * @param pListener Is called whenever there is a new gesture of the
     * specified type. The caller of this function owns pListener and is
     * responsible for keeping it alive until unregisterGestureListener() has
     * been called, or until this Engine instance has been destroyed.
     *
     * @return #TA3D_RESULT_OK if the operation was successful.<br>
     * #TA3D_RESULT_INVALID_INPUT if pListener is zero.<br>
     * #TA3D_RESULT_WRONG_INTERNAL_STATE if init() has not been called on this
     * Engine instance.
     * #TA3D_OUT_OF_MEMORY if a memory allocation fails.
     */
    int registerGestureListener(GestureType eType, GestureListener *pListener);

    /**
     * Unregisters a listener for a specific type of gesture.
     *
     * If the listener has been registered more than once for the specified
     * gesture type, only one of the registrations is removed.
     *
     * Example usage:
     *
     * @code
     * pEngine->unregisterGestureListener(OpenHandPresence::TYPE, pListener);
     * @endcode
     *
     * @see registerGestureListener()
     *
     * @param eType The type of gesture to stop listening for.
     * @param pListener Will no longer be called when there is a new gesture of
     * the specified type.
     *
     * @return #TA3D_RESULT_OK if the operation was successful.<br>
     * #TA3D_RESULT_INVALID_INPUT if pListener is zero.<br>
     * #TA3D_RESULT_WRONG_INTERNAL_STATE if init() has not been called on this
     * Engine instance.
     * #TA3D_OUT_OF_MEMORY if a memory allocation fails.
     */
    int unregisterGestureListener(GestureType eType, GestureListener *pListener);

    /**
     * Lets this Engine instance do calculations on a new image.
     *
     * Might cause gestures to be emitted.
     *
     * @param uTimestamp Timestamp for the input image, in milliseconds. Must
     * be a higher value than in any previous call to this method.
     * @param pImageData Pixel data for the input image. The array must have a
     * size of at least imageWidth * imageHeight elements, where imageWidth and
     * imageHeight are the parameters given in the call to init().
     * The data must be given as row-by-row grayscale values. That is, the
     * first imageWidth number of elements must contain grayscale values for
     * the first row in the image. The second imageWidth number of elements
     * must contain grayscale values for the second row in the image, etc.
     * The byte array given by the Android device as parameter to the
     * android.hardware.Camera.PreviewCallback Java interface method
     * onPreviewFrame(byte[], android.hardware.Camera) fullfills this requirement.
     * @param eRotate Specifies how this Engine instance should rotate
     * the input image internally before performing calculations on it.
     *
     * @return #TA3D_RESULT_OK if the operation was successful.<br>
     * #TA3D_RESULT_INVALID_INPUT if pImageData is zero.<br>
     * #TA3D_RESULT_WRONG_INTERNAL_STATE if init() has not been called on this
     * Engine instance.
     * #TA3D_OUT_OF_MEMORY if a memory allocation fails.
     */
    int handleImage(unsigned long long uTimestamp, unsigned char *pImageData,
      Rotate eRotate = DO_NOT_ROTATE);
    
    /**
     * @return A value in the range 0 - 100. 30 or higher means that the
     * exposure time should be increased. 50 or higher means that the image
     * is so dark that A3D will not try to find any faces or hands in the
     * input images.
     */
    int getBlackLevel();
  };

}  // namespace TouchlessA3D


#endif
