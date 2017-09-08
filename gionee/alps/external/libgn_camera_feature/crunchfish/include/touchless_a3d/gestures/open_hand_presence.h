#ifndef OPEN_HAND_PRESENCE_AWNFEADLSNF
#define OPEN_HAND_PRESENCE_AWNFEADLSNF

#include "../object_presence.h"


namespace TouchlessA3D {

  /**
   * Emitted when open hands are present in the input images to Engine#handleImage().
   *
   * Whenever a new open hand is detected in an input image, an %OpenHandPresence
   * object with the Action START is emitted. After that, an %OpenHandPresence
   * object with the Action MOVEMENT is emitted for every input image in which
   * the open hand is still seen. When the open hand is no longer found in the
   * input images, an %OpenHandPresence object with the Action END is sent.
   * After that, no more %OpenHandPresence objects are sent for that object id,
   * but objects with a new id will be sent if an open hand is again seen in the input images. 
   * 
   * Copyright © 2013 Crunchfish AB. All rights reserved. All information herein is
   * or may be trade secrets of Crunchfish AB.
   */
  class TA3D_EXPORT OpenHandPresence : public ObjectPresence {
  public:
    static const GestureType TYPE = 0;

    OpenHandPresence(unsigned long long uTime, int nObjectId, Action eAction,
      int x, int y, int z, int prevX, int prevY, int prevZ, int nWidth, int nHeight);
    Gesture *clone() const;
    GestureType getType() const;
  };

}  // namespace TouchlessA3D


#endif
