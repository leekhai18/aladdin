/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "Transform.h"
#include "StdHelper.h"
#include "GameManager.h"

NAMESPACE_ALA
{
// ===================================================
// Basic
// ===================================================

ALA_CLASS_SOURCE_1( ala::Transform, ala::GameObjectComponent )

Transform::Transform( GameObject* gameObject, Transform* parentTransform, const std::string& name )
  : GameObjectComponent( gameObject, name ),
    _position( 0, 0 ),
    _scale( 1, 1 ),
    _rotation( 0 ),
    _origin( 0.5f, 0.5f ),
    _childrenInLocking( false ),
    _parent( parentTransform ),
    _dirty( true ),
    _inverseDirty( true ) {
  if ( _parent != NULL ) {
    _localToWorldMatrix = Mat4::getIdentityMat();
    _worldToLocalMatrix = Mat4::getIdentityMat();
    _parent->addChild( this );
  }
}

Transform::~Transform() {}

const Vec2& Transform::getPosition() const {
  return _position;
}

float Transform::getPositionX() const {
  return _position.getX();
}

float Transform::getPositionY() const {
  return _position.getY();
}

void Transform::setPosition( const Vec2& position ) {
  _position = position;
  setDirty();
}

void Transform::setPosition( const float x, const float y ) {
  _position = Vec2( x, y );
  setDirty();
}

void Transform::setPositionX( const float x ) {
  _position.setX( x );
  setDirty();
}

void Transform::setPositionY( const float y ) {
  _position.setY( y );
  setDirty();
}

const Vec2& Transform::getScale() const {
  return _scale;
}

void Transform::setScale( const Vec2& scale ) {
  _scale = scale;
  setDirty();
}

void Transform::setScaleX( const float x ) {
  _scale.setX( x );
  setDirty();
}

void Transform::setScaleY( const float y ) {
  _scale.setY( y );
  setDirty();
}

void Transform::setScale( const float scale ) {
  _scale.setX( scale );
  _scale.setY( scale );
  setDirty();
}

float Transform::getRotation() const {
  return _rotation;
}

void Transform::setRotation( const float rotation ) {
  _rotation = rotation;
  setDirty();
}

// =======================================================
// Children management
// =======================================================

std::vector<Transform*> Transform::getChildren() const {
  return _children;
}

Transform* Transform::getChild( const int index ) const {
  return _children[index];
}

Transform* Transform::getParent() const {
  return _parent;
}

void Transform::addChild( Transform* child ) {
  // check lock
  if ( _childrenInLocking ) {
    addChildInNextFrame( child );
    return;
  }

  if ( isReleasing() || isReleased() ) return;
  if ( child == NULL ) return;
  if ( StdHelper::vectorContain( _children, child ) ) return;
  doAddChild( child );
}

void Transform::addChildInNextFrame( Transform* child ) {
  if ( isReleasing() || isReleased() ) return;
  if ( child == NULL ) return;
  if ( StdHelper::vectorContain( _children, child ) ) return;
  _childrenToAddInNextFrame.push_back( child );
}

void Transform::removeChild( Transform* child ) {
  // check lock
  if ( _childrenInLocking ) {
    removeChildInNextFrame( child );
    return;
  }

  if ( isReleasing() || isReleased() ) return;
  if ( child == NULL ) return;
  doRemoveChild( child );
}

void Transform::removeChildInNextFrame( Transform* child ) {
  if ( isReleasing() || isReleased() ) return;
  if ( child == NULL ) return;
  _childrenToRemoveInNextFrame.push_back( child );
}

void Transform::lockChildren() {
  _childrenInLocking = true;
}

void Transform::unlockChildren() {
  _childrenInLocking = false;
}

void Transform::updateAddAndRemoveChildInNextFrame() {
  for ( auto child : _childrenToAddInNextFrame ) {
    doAddChild( child );
  }
  _childrenToAddInNextFrame.clear();

  for ( auto child : _childrenToRemoveInNextFrame ) {
    doRemoveChild( child );
  }
  _childrenToRemoveInNextFrame.clear();
}

void Transform::doAddChild( Transform* child ) {
  _children.push_back( child );
}

void Transform::doRemoveChild( Transform* child ) {
  StdHelper::vectorErase( _children, child );
}

bool Transform::onPreRelease() {
  if ( _childrenInLocking ) {
    releaseInNextFrame();
    return false;
  }
  return true;
}

void Transform::onRelease() {
  // release child transform
  for ( auto child : _children ) {
    child->getGameObject()->release();
  }
  if ( _parent != NULL ) {
    _parent->removeChild( this );
  }
}

void Transform::onPreUpdate( const float delta ) {
  updateAddAndRemoveChildInNextFrame();
}

void Transform::onUpdate( const float delta ) {
  lockChildren();

  for ( auto transform : _children ) {
    transform->getGameObject()->update( delta );
  }

  unlockChildren();
}

void Transform::onRender() {
  lockChildren();

  for ( auto transform : _children ) {
    transform->getGameObject()->render();
  }

  unlockChildren();
}

Mat4 Transform::calculateLocalToParentMatrix() const {
  Mat4 matRotate = Mat4::getRotationZMatrix( D3DXToRadian(_rotation) );
  Mat4 matScale = Mat4::getScalingMatrix( _scale );
  Mat4 matTranslate = Mat4::getTranslationMatrix( _position );

  return matRotate * matScale * matTranslate;
}

Mat4 Transform::getLocalToWorldMatrix() {
  if ( _dirty ) {
    if ( _parent == NULL ) {
      _localToWorldMatrix = calculateLocalToParentMatrix();
    }
    else {
      _localToWorldMatrix = _parent->getLocalToWorldMatrix() * calculateLocalToParentMatrix();
    }

    _dirty = false;
  }

  return _localToWorldMatrix;
}

Mat4 Transform::getWorldToLocalMatrix() {
  if ( _inverseDirty ) {
    auto localToWorldMatrix = getLocalToWorldMatrix();
    _worldToLocalMatrix = localToWorldMatrix.getInverse();
    _inverseDirty = false;
  }

  return _worldToLocalMatrix;
}

void Transform::setDirty() {
  if ( !_dirty ) {
    _dirty = true;
    _inverseDirty = true;

    for ( auto transform : _children ) {
      transform->setDirty();
    }
  }
}
}
