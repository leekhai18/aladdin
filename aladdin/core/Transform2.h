/*
 * Created by phuctm97 on Sep 30th 2017
 */

#ifndef __ALADDIN_CORE_TRANSFORM2_H__
#define __ALADDIN_CORE_TRANSFORM2_H__

#include "GameObjectComponent.h"
#include "Vec2.h"
#include "Mat4.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1(Transform, ala::GameObjectComponent)

  // ===================================================
  // Basic
  // ===================================================
private:
  Vec2 _position;
  Vec2 _scale;
  float _rotation;
  Vec2 _origin;
public:
  Transform( GameObject* gameObject, Transform* parentTransform = NULL, const std::string& name = "" );

  virtual ~Transform();

  const Vec2& getPosition() const;

  float getPositionX() const;

  float getPositionY() const;

  void setPosition( const Vec2& position );

  void setPosition( const float x, const float y );

  void setPositionX( const float x );

  void setPositionY( const float y );

  const Vec2& getScale() const;

  void setScale( const Vec2& scale );

  void setScaleX( const float x );

  void setScaleY( const float y );

  void setScale( const float scale );

  float getRotation() const;

  void setRotation( const float rotation );

  // =======================================================
  // Children management
  // =======================================================

private:
  bool _childrenInLocking;
  std::vector<Transform*> _children;
  Transform* _parent;
  std::vector<Transform*> _childrenToAddInNextFrame;
  std::vector<Transform*> _childrenToRemoveInNextFrame;

public:
  std::vector<Transform*> getChildren() const;

  Transform* getChild( const int index ) const;

  Transform* getParent() const;

  /**
   * \brief Attach a transform as child of this transform, this will not remove child from old parent and change its parent, you should not call this method directly
   * \param child Child transform to attach
   */
  void addChild( Transform* child );

  void addChildInNextFrame( Transform* child );

  /**
   * \brief Detach a transform from this children, this will not reset child parent or object, you should not call this method directly
   * \param child Child transform to detach
   */
  void removeChild( Transform* child );

  void removeChildInNextFrame( Transform* child );

private:
  void lockChildren();

  void unlockChildren();

  void updateAddAndRemoveChildInNextFrame();

  void doAddChild( Transform* child );

  void doRemoveChild( Transform* child );

protected:
  bool onPreRelease() override;
  
  void onRelease() override;

  void onPreUpdate( const float delta ) override;

  void onUpdate( const float delta ) override;

  void onRender() override;

  // =====================================================
  // Transformation
  // =====================================================
public:
  Mat4 calculateLocalToParentMatrix() const;

  Mat4 getLocalToWorldMatrix();

  Mat4 getWorldToLocalMatrix();
private:
  // specifies if the localToWorldTransform
  // needs to be recalulated
  bool _dirty;
  // the transform that converts local coordinates
  // to world coordinates
  Mat4 _localToWorldMatrix;
  // specifies if the worldToLocalMatrix
  // needs to be recalculated
  bool _inverseDirty;
  // the transform that converts world cooridnates
  // to local coordinates
  Mat4 _worldToLocalMatrix;

  void setDirty();
};
}

#endif //!__ALADDIN_CORE_TRANSFORM2_H__
