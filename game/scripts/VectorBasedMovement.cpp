#include "VectorBasedMovement.h"

USING_NAMESPACE_ALA;

VectorBasedMovement::VectorBasedMovement( ala::GameObject* gameObject, const std::string& name )
  : GameObjectComponent( gameObject, name ), _vector( 0, 0 ) {}

void VectorBasedMovement::setVector( const ala::Vec2& vector ) {
  _vector = vector;
}

void VectorBasedMovement::setVectorX( const float x ) {
  _vector.setX( x );
}

void VectorBasedMovement::setVectorY( const float y ) {
  _vector.setY( y );
}

const ala::Vec2& VectorBasedMovement::getVector() const {
  return _vector;
}

void VectorBasedMovement::onUpdate( const float delta ) {
  auto transform = getGameObject()->getTransform();

  const auto newPosition = transform->getPosition() + _vector * delta;
  transform->setPosition( newPosition );
}
