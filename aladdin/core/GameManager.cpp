/*
* Created by phuctm97 on Sep 27th 2017
*/

#include "GameManager.h"

NAMESPACE_ALA
{
// ===========================================
// Basic
// ===========================================

ALA_CLASS_SOURCE_1(ala::GameManager, ala::Releasable)

GameManager* GameManager::__instance( NULL );

GameManager* GameManager::get() {
  if ( __instance == NULL ) {
    __instance = new GameManager();
  }
  return __instance;
}

GameManager::GameManager() :
  _logger( "ala::GameManager" ),
  _screenWidth( 0 ),
  _screenHeight( 0 ),
  _idCounter( 0 ),
  _runningScene( NULL ),
  _sceneToReplaceInNextFrame( NULL ),
  _globalMessenger( new Messenger() ) {
  ALA_ASSERT((!isReleased()) && (!isReleasing()));
  _logger.debug( "Created" );
}

GameManager::~GameManager() {
  ALA_ASSERT(isReleased());
  _logger.debug( "Released" );
}

void GameManager::update( const float delta ) {
  if ( isReleasing() || isReleased() ) return;

  updateRunningScene();
}

void GameManager::release() {
  ALA_ASSERT((!isReleased()) && (!isReleasing()));

  setToReleasing();

  // release messenger
  _globalMessenger->release();

  setToReleased();

  // destroy
  delete this;
}

// ==============================================
// Game Information
// ==============================================
float GameManager::getScreenWidth() const {
  return _screenWidth;
}

float GameManager::getScreenHeight() const {
  return _screenHeight;
}

// =============================================
// Id Generator
// =============================================
long GameManager::newId() {
  return ++_idCounter;
}

// ==============================================
// Object Management
// ==============================================

void GameManager::attach( Node* gameObject ) {
  if ( isReleasing() || isReleased() ) return;
  if ( gameObject == NULL ) return;
  _attachedNodes.emplace( gameObject->getId(), gameObject );
}

void GameManager::detach( Node* gameObject ) {
  if ( isReleasing() || isReleased() ) return;
  if ( gameObject == NULL ) return;
  _attachedNodes.erase( gameObject->getId() );
}

std::vector<Node*> GameManager::getAllNodes() {
  std::vector<Node*> ret;

  for ( const auto it : _attachedNodes ) {
    ret.push_back( it.second );
  }

  return ret;
}

Node* GameManager::getNodeById( const long id ) {
  const auto objectIt = _attachedNodes.find( id );
  if ( objectIt == _attachedNodes.end() ) return NULL;

  const auto object = objectIt->second;
  return object;
}

std::vector<Node*> GameManager::getAllNodesByName( const std::string& name ) {
  std::vector<Node*> ret;

  for ( auto& pair : _attachedNodes ) {
    auto object = pair.second;
    if ( object == NULL ) continue;
    if ( object->getName() == name ) {
      ret.emplace_back( object );
    }
  }

  return ret;
}

Node* GameManager::getNodeByName( const std::string& name ) {
  for ( auto& pair : _attachedNodes ) {
    const auto object = pair.second;
    if ( object == NULL ) continue;
    if ( object->getName() == name ) {
      return object;
    }
  }
  return NULL;
}

// ==================================================
// Scene Management
// ==================================================

Scene* GameManager::getRunningScene() const {
  return _runningScene;
}

void GameManager::replaceScene( Scene* scene ) {
  if ( isReleasing() || isReleased() ) return;
  if ( scene == NULL ) return;
  if ( scene == _runningScene ) return;
  doReplaceScene( scene );
}

void GameManager::replaceSceneInNextFrame( Scene* scene ) {
  if ( isReleasing() || isReleased() ) return;
  if ( scene == NULL ) return;
  if ( scene == _runningScene ) return;
  _sceneToReplaceInNextFrame = scene;
}

void GameManager::updateRunningScene() {
  if ( _sceneToReplaceInNextFrame == NULL ) return;
  doReplaceScene( _sceneToReplaceInNextFrame );
  _sceneToReplaceInNextFrame = NULL;
}

void GameManager::doReplaceScene( Scene* scene ) {
  if ( _runningScene != NULL ) {
    _runningScene->release();
  }

  _runningScene = scene;
  if ( !_runningScene->isInitialized() ) {
    _runningScene->initialize();
  }
}

// ===============================================
// Resource Management
// ===============================================

void GameManager::attach( GameResource* resource ) {
  if ( isReleasing() || isReleased() ) return;
  if ( resource == NULL ) return;
  auto rc = _attachedResources.emplace( resource->getName(), resource );

  // make sure there is no duplicate resources
  ALA_ASSERT(rc.second == true);
}

void GameManager::detach( GameResource* resource ) {
  if ( isReleasing() || isReleased() ) return;
  if ( resource == NULL ) return;
  _attachedResources.erase( resource->getName() );
}

GameResource* GameManager::getResource( const std::string& name ) {
  const auto it = _attachedResources.find( name );
  if ( it == _attachedResources.end() ) return NULL;
  return it->second;
}

std::vector<GameResource*> GameManager::getResourcesWith( Scene* scope ) {
  std::vector<GameResource*> ret;

  for ( const auto it : _attachedResources ) {
    auto resource = it.second;
    if ( resource->getSceneScope() == scope ) {
      ret.push_back( resource );
    }
  }

  return ret;
}

std::vector<GameResource*> GameManager::getAllResources() {
  std::vector<GameResource*> ret;

  for ( const auto it : _attachedResources ) {
    auto resource = it.second;
    ret.push_back( resource );
  }

  return ret;
}

// ===============================================
// Global messenger
// ===============================================

Messenger* GameManager::getGlobalMessenger() const {
  return _globalMessenger;
}
}
