#ifndef FACE_PRESENCE_AWNFEADLSNF
#define FACE_PRESENCE_AWNFEADLSNF

#include "../object_presence.h"


namespace TouchlessA3D {

  /**
   * Emitted when faces are present in the input images to Engine#handleImage().
   *
   * Whenever a new face is detected in an input image, a %FacePresence
   * object with the Action START is emitted. After that, a %FacePresence
   * object with the Action MOVEMENT is emitted for every input image in which
   * the face is still seen. When the open hand is no longer found in the
   * input images, a %FacePresence object with the Action END is sent.
   * After that, no more %FacePresence objects are sent for that object id,
   * but objects with a new id will be sent if a face is again seen in the input images. 
   * 
   * Copyright © 2013 Crunchfish AB. All rights reserved. All information herein is
   * or may be trade secrets of Crunchfish AB.
   */
  class TA3D_EXPORT FacePresence : public ObjectPresence {
  public:
    static const GestureType TYPE = 2;

    FacePresence(unsigned long long uTime, int nObjectId, Action eAction,
      int x, int y, int z, int prevX, int prevY, int prevZ, int nWidth, int nHeight);
    Gesture *clone() const;
    GestureType getType() const;
  };

}  // namespace TouchlessA3D


#endif
