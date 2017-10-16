/*
* Created by phuctm97 on Sep 27th 2017
*/

#include "GameObjectComponent.h"
#include "GameObject.h"

NAMESPACE_ALA
{
// ================================================
// Basic
// ================================================

ALA_CLASS_SOURCE_2(GameObjectComponent, ala::Initializable, ala::Releasable)

GameObjectComponent::GameObjectComponent( GameObject* gameObject, const std::string& name )
  : _name( name ),
    _gameObject( gameObject ),
    _active( false ),
    _toReleaseInNextFrame( false ) {
  // check initial state
  ALA_ASSERT((!isInitialized()) && (!isInitializing()) && (!isReleased()) && (!isReleasing()));

  // check game object
  ALA_ASSERT(gameObject != NULL);

  // attach to game object
  _gameObject->addComponent( this );

  TOTAL_COMPONENTS_CREATED++;
}

GameObjectComponent::~GameObjectComponent() {
  if ( isInitialized() ) {
    // make sure object released after destruction
    ALA_ASSERT(isReleased());
  }

  TOTAL_COMPONENTS_DELETED++;
}

const std::string& GameObjectComponent::getName() const {
  return _name;
}

GameObject* GameObjectComponent::getGameObject() const {
  return _gameObject;
}

bool GameObjectComponent::isActive() const {
  return _active;
}

void GameObjectComponent::setActive( const bool val ) {
  _active = val;
}

bool GameObjectComponent::isSelfInitialize() const {
  return _selfInitialize;
}

void GameObjectComponent::setSelfInitialize( const bool val ) {
  _selfInitialize = val;
}

// =================================================
// Events
// =================================================

void GameObjectComponent::initialize() {
  // make sure object is not initialized;
  ALA_ASSERT((!isInitialized()) && (!isInitializing()));

  if ( !onPreInitialize() ) return;

  setToInitializing();

  // TODO: lock mutual exclusive when run in multithreading mode

  onInitialize();

  setToInitialized();

  // activate
  setActive( true );
}

void GameObjectComponent::onInitialize() {}

bool GameObjectComponent::onPreInitialize() {
  return true;
}

void GameObjectComponent::update( const float delta ) {
  if ( isReleasing() || isReleased() ) return;

  // update to release in next frame
  if ( _toReleaseInNextFrame ) {
    release();
    _toReleaseInNextFrame = false;
    return;
  }

  onPreUpdate( delta );

  if ( !isInitialized() ) {
    if ( isSelfInitialize() ) {
      initialize();
    }
    else return;
  }

  if ( !isActive() ) return;

  // inheritance update
  onUpdate( delta );
}

void GameObjectComponent::onUpdate( const float delta ) {}

void GameObjectComponent::onPreUpdate( const float delta ) {}

void GameObjectComponent::onRender() {}

void GameObjectComponent::render() {
  if ( (!isInitialized()) || isReleasing() || isReleased() ) return;

  onRender();
}

void GameObjectComponent::release() {
  // make sure object is initialized and not released
  ALA_ASSERT((isInitialized()) && (!isReleasing()) && (!isReleased()));

  if ( !onPreRelease() ) return;

  setToReleasing();

  // TODO: lock mutual exclusive when run in multithreading mode

  onRelease();

  // remove from game object
  _gameObject->removeComponent( this );

  setToReleased();

  // destroy
  delete this;
}

void GameObjectComponent::releaseInNextFrame() {
  // make sure object is initialized and not released
  ALA_ASSERT((isInitialized()) && (!isReleasing()) && (!isReleased()));
  _toReleaseInNextFrame = true;
}

void GameObjectComponent::onRelease() {}

bool GameObjectComponent::onPreRelease() {
  return true;
}

// ===========================================================
// Debug memory allocation
// ===========================================================
long GameObjectComponent::TOTAL_COMPONENTS_CREATED( 0 );
long GameObjectComponent::TOTAL_COMPONENTS_DELETED( 0 );
}
