#ifndef GESTURE_LISTENER_AOWFEHOAWFNAONN
#define GESTURE_LISTENER_AOWFEHOAWFNAONN

#include "gesture.h"


namespace TouchlessA3D {

  /**
   * Abstract base class for gesture listeners implemented by the user of this library.
   *
   * Copyright © 2013 Crunchfish AB. All rights reserved. All information herein
   * is or may be trade secrets of Crunchfish AB.
   */
  class TA3D_EXPORT GestureListener {
  public:
    virtual ~GestureListener();

    /**
     * Called from an Engine instance whenever it has a new Gesture object
     * of the type for which this listener instance has been registered.
     *
     * Example implementation:
     *
     * @code
void MyClass::onGesture(const Gesture *pGesture) {
  if (pGesture->getType() == OpenHandPresence::TYPE) {
    OpenHandPresence *pOpenHandPresence = static_cast<OpenHandPresence*>(pGesture);
    ...
  } else if (pGesture->getType() == FacePresence::TYPE) {
    FacePresence *pFacePresence = static_cast<FacePresence*>(pGesture);
    ...
  }
}
     * @endcode
     *
     * @see Engine#registerGestureListener()
     *
     * @param pGesture A pointer to the new Gesture object emitted by the
     * Engine instance on which this listener instance has been registered.
     */
    virtual void onGesture(const Gesture *pGesture) = 0;
  };

}  // namespace TouchlessA3D

#endif
