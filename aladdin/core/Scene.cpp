/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "Scene.h"
#include "StdHelper.h"
#include "GameResource.h"
#include "GameManager.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_2(ala::Scene, ala::Initializable, ala::Releasable)

// ================================================
// Basic
// ================================================

Scene::Scene(): _toReleaseInNextFrame( false ), _nodeInLocking( false ) {
  // check initial state
  ALA_ASSERT((!isInitialized()) && (!isInitializing()) && (!isReleased()) && (!isReleasing()));

  TOTAL_SCENES_CREATED++;
}

Scene::~Scene() {
  if ( isInitialized() ) {
    // make sure object released after destruction
    ALA_ASSERT(isReleased());
  }

  TOTAL_SCENES_DELETED++;
}

// =================================================
// Events
// =================================================

void Scene::initialize() {
  // make sure scene is not initialized;
  ALA_ASSERT((!isInitializing()) && (!isInitialized()));

  onPreInitialize();

  setToInitializing();

  // TODO: lock mutual exclusive when run in multithreading mode

  // load resources scope with this
  for ( auto resource : GameManager::get()->getResourcesWith( this ) ) {
    if ( !resource->isLoaded() ) {
      resource->load();
    }
  }

  // init game objects
  for ( const auto it : _nodes ) {
    auto object = it.second;

    if ( !object->isInitialized() ) {
      object->initialize();
    }
  }

  setToInitialized();

  onPostInitialize();
}

void Scene::onPreInitialize() {}

void Scene::onPostInitialize() {}

void Scene::update( const float delta ) {
  if ( isReleasing() || isReleased() ) return;

  // update to release in next frame
  if ( _toReleaseInNextFrame ) {
    release();
    _toReleaseInNextFrame = false;
    return;
  }

  // update actions
  updateAddAndRemoveNodes();

  if ( !isInitialized() ) return;

  lockNodes();

  onPreUpdate( delta );

  // update game objects
  for ( const auto it : _nodes ) {
    auto object = it.second;
    object->update( delta );
  }

  onPostUpdate( delta );

  unlockNodes();
}

void Scene::onPreUpdate( const float delta ) {}

void Scene::onPostUpdate( const float delta ) {}

void Scene::render() {
  // make sure scene is initialized and not being released
  if ( (!isInitialized()) || isReleasing() || isReleased() ) return;

  lockNodes();

  onPreRender();

  // render game objects
  for ( const auto it : _nodes ) {
    auto object = it.second;
    object->render();
  }

  onPostRender();

  unlockNodes();
}

void Scene::onPreRender() {}

void Scene::onPostRender() {}

void Scene::release() {
  // check lock
  if ( _nodeInLocking ) {
    releaseInNextFrame();
    return;
  }

  // make sure scene is initialized and not released
  ALA_ASSERT(isInitialized() && (!isReleasing()) && (!isReleased()));

  onPreRelease();

  setToReleasing();

  // release game objects
  std::vector<Node*> nodesToRelease;
  for ( const auto it : _nodes ) {
    auto object = it.second;
    object->release();
  }

  // release resources scope with this
  for ( auto resouce : GameManager::get()->getResourcesWith( this ) ) {
    resouce->release();
  }

  setToReleased();

  onPostRelease();

  // destroy
  delete this;
}

void Scene::releaseInNextFrame() {
  // make sure scene is initialized and not released
  ALA_ASSERT(isInitialized() && (!isReleasing()) && (!isReleased()));
  _toReleaseInNextFrame = true;
}

void Scene::onPreRelease() {}

void Scene::onPostRelease() {}

// ==================================================
// Objects Management
// ==================================================

Node* Scene::getNode( const long id ) {
  const auto it = _nodes.find( id );
  if ( it == _nodes.end() ) return NULL;
  return it->second;
}

void Scene::addNode( Node* node ) {
  // check lock
  if ( _nodeInLocking ) {
    addNodeInNextFrame( node );
    return;
  }

  if ( isReleasing() || isReleased() ) return;
  if ( node == NULL ) return;
  doAddNode( node );
}

void Scene::addNodeInNextFrame( Node* node ) {
  if ( isReleasing() || isReleased() ) return;
  if ( node == NULL ) return;
  _nodesToAddInNextFrame.push_back( node );
}

void Scene::removeNode( Node* node ) {
  // check lock
  if ( _nodeInLocking ) {
    removeNodeInNextFrame( node );
    return;
  }

  if ( isReleasing() || isReleased() ) return;
  if ( node == NULL ) return;
  doRemoveNode( node );
}

void Scene::removeNodeInNextFrame( Node* node ) {
  if ( isReleasing() || isReleased() ) return;
  if ( node == NULL ) return;
  _nodesToRemoveInNextFrame.push_back( node );
}

void Scene::lockNodes() {
  _nodeInLocking = true;
}

void Scene::unlockNodes() {
  _nodeInLocking = false;
}

void Scene::updateAddAndRemoveNodes() {
  for ( auto object : _nodesToAddInNextFrame ) {
    doAddNode( object );
  }
  _nodesToAddInNextFrame.clear();

  for ( auto object : _nodesToRemoveInNextFrame ) {
    doRemoveNode( object );
  }
  _nodesToRemoveInNextFrame.clear();
}

void Scene::doAddNode( Node* node ) {
  _nodes.emplace( node->getId(), node );
}

void Scene::doRemoveNode( Node* node ) {
  _nodes.erase( node->getId() );
}

// =============================================
// Debug memory allocation
// =============================================
long Scene::TOTAL_SCENES_CREATED( 0 );
long Scene::TOTAL_SCENES_DELETED( 0 );
}
