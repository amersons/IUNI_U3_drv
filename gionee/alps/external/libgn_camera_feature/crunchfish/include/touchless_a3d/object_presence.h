#ifndef OBJECT_PRESENCE_OANFEOAWF
#define OBJECT_PRESENCE_OANFEOAWF

#include "gesture.h"


namespace TouchlessA3D {

  /**
   * Abstract base class for gesture classes of the presence types.
   *
   * Presence gestures are emitted when objects of the specified type (for
   * example open hands or faces) are present in the input images. Each type
   * of object that can be detected is represented by a subclass of ObjectPresence.
   *
   * Copyright © 2013 Crunchfish AB. All rights reserved. All information herein
   * is or may be trade secrets of Crunchfish AB.
   */
  class TA3D_EXPORT ObjectPresence : public Gesture {
  public:
    /**
     * Each sequence of emitted ObjectPresence gestures for a specific object
     * starts with an ObjectPresence gesture having the Action START and ends
     * with an ObjectPresence gesture having the Action END. All gestures
     * between the first and the last one have the Action MOVEMENT.
     */
    enum Action {
      START = 0,
      MOVEMENT,
      END
    };

  protected:
    int m_nObjectId, m_x, m_y, m_z, m_prevX, m_prevY, m_prevZ, m_nWidth, m_nHeight;
    Action m_eAction;

    ObjectPresence(unsigned long long uTime, int nObjectId, Action eAction,
      int x, int y, int z, int prevX, int prevY, int prevZ, int nWidth, int nHeight);

  public:
    /**
     * Gets the unique id of the tracked object.
     *
     * @return An identifier for a specific object in the input images.
     * For example, if there are two hands currently visible in the input
     * images, they will each have a unique ObjectId value that stays
     * the same for all gestures concerning that specific object. 
     */
    int getObjectId() const;

    /**
     * @return Specifies which part of the gesture life cycle this gesture
     * instance represents.
     */
    Action getAction() const;

    /**
     * @return The x coordinate of the center of the object specified by
     * getObjectId(). The position is given as a coordinate in the
     * input image. The position can in some cases exceed the image bounds.
     */
    int getCenterX() const;

    /**
     * @return The y coordinate of the center of the object specified by
     * getObjectId(). The position is given as a coordinate in the
     * input image. The position can in some cases exceed the image bounds.
     */
    int getCenterY() const;

    /**
     * @return The relative z coordinate of the object specified by
     * getObjectId(). When getAction() returns START, this
     * method returns zero. All z values later returned by this method for the
     * object specified by getObjectId() are relative to that initial
     * position.
     */
    int getZ() const;

    /**
     * @return The center x coordinate in the previous gesture of this type for
     * the object specified by getObjectId().
     */
    int getPrevCenterX() const;

    /**
     * @return The center y coordinate in the previous gesture of this type for
     * the object specified by getObjectId().
     */
    int getPrevCenterY() const;

    /**
     * @return The relative z coordinate in the previous gesture of this type
     * for the object specified by getObjectId().
     */
    int getPrevZ() const;

    /**
     * @return The width of the object specified by getObjectId(), at
     * the time specified by getTimestamp(). The range of the returned
     * value is from one to the width of the input image after any rotation
     * specified in the call to Engine#handleImage().
     */
    int getWidth() const;

    /**
     * @return The height of the object specified by getObjectId(), at
     * the time specified by getTimestamp(). The range of the returned
     * value is from one to the height of the input image after any rotation
     * specified in the call to Engine#handleImage().
     */
    int getHeight() const;
  };

}  // namespace TouchlessA3D


#endif
