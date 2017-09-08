#ifndef GESTURE_OAHJFOAHFOALA
#define GESTURE_OAHJFOAHFOALA

#ifdef ANDROID
#  define TA3D_EXPORT __attribute__ ((visibility ("default")))
#elif defined(_WIN32)
#  define TA3D_EXPORT __declspec(dllexport)
#else
#  define TA3D_EXPORT
#endif


namespace TouchlessA3D {

  /**
   * Used as a unique identifier for the different types of gestures.
   *
   * Is used as argument in calls to the functions
   * Engine#registerGestureListener() and Engine#unregisterGestureListener().
   */
  typedef int GestureType;


  /**
   * Abstract base class for all gesture classes.
   *
   * Copyright © 2013 Crunchfish AB. All rights reserved. All information herein
   * is or may be trade secrets of Crunchfish AB.
   */
  class TA3D_EXPORT Gesture {
  protected:
    unsigned long long m_uTimestamp;

  public:
    /**
     * @param uTimestamp Timestamp in milliseconds for when this Gesture object
     * was emitted.
     */
    explicit Gesture(unsigned long long uTimestamp);
    virtual ~Gesture();

    /**
     * This function makes it possible to clone a Gesture object without first
     * converting it to its specific subclass.
     *
     * Since the memory for the clone is allocated by the Crunchfish %TouchlessA3D
     * library, the memory must also be released by the Crunchfish %TouchlessA3D
     * library when the clone is no longer needed. That can be achieved by
     * calling destroy(). Do not try to delete a clone in any other way.
     *
     * @see destroy()
     *
     * @return A pointer to a newly allocated clone of this Gesture object.
     */
    virtual Gesture *clone() const = 0;

    /**
     * Releases the memory allocated for this Gesture object.
     *
     * Must only be called on Gesture objects that were created by calling
     * clone() on another Gesture object.
     *
     * After calling this function, this Gesture object becomes invalid.
     */
    void destroy();

    /**
     * Use this function to find out the subclass of this Gesture object.
     *
     * Example usage in an implementation of GestureListener#onGesture():
     *
     * @code
     * if (pGesture->getType() == OpenHandPresence::TYPE) {
     *   OpenHandPresence *pOpenHandPresence = static_cast<OpenHandPresence*>(pGesture);
     *   ...
     * @endcode
     *
     * @return The type identification of this Gesture object.
     */
    virtual GestureType getType() const = 0;
    
    /**
     * Returns timestamp in milliseconds.
     *
     * @return Timestamp in milliseconds for when this Gesture object
     * was emitted.
     */
    unsigned long long getTimestamp() const;
  };

}  // namespace TouchlessA3D

#endif
