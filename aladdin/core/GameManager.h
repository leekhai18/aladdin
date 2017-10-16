#ifndef __ALADDIN_CORE_GAME_MANAGER_H__
#define __ALADDIN_CORE_GAME_MANAGER_H__

/*
* Created by phuctm97 on Sep 27th 2017
*/

#include "Node.h"
#include "Scene.h"
#include "GameResource.h"
#include "Logger.h"
#include "Messenger.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1(GameManager, ala::Releasable)
  // ==============================================
  // Basic
  // ==============================================
  friend class Application;

private:
  static GameManager* __instance;
  Logger _logger;

public:
  GameManager();

  virtual ~GameManager();

  static GameManager* get();

  void update( const float delta );

  void release() override;

  // ===============================================
  // Game Information
  // ===============================================
private:
  float _screenWidth;
  float _screenHeight;

public:
  float getScreenWidth() const;
  float getScreenHeight() const;

  // ===============================================
  // Id Generator
  // ===============================================
private:
  long _idCounter;

public:
  long newId();

  // ===============================================
  // Object Management
  // ===============================================
private:
  std::unordered_map<long, Node*> _attachedNodes;

public:
  void attach( Node* node );

  void detach( Node* node);

  std::vector<Node*> getAllNodes();

  Node* getNodeById( const long id );

  template <class T>
  T* getNodeTById( const long id );

  std::vector<Node*> getAllNodesByName( const std::string& name );

  Node* getNodeByName( const std::string& name );

  template <class T>
  T* getNodeTByName( const std::string& name );

  // ===============================================
  // Scene Management
  // ===============================================
private:
  Scene* _runningScene;
  Scene* _sceneToReplaceInNextFrame;

public:
  Scene* getRunningScene() const;

  void replaceScene( Scene* scene );

  void replaceSceneInNextFrame( Scene* scene );

private:
  void updateRunningScene();
  void doReplaceScene( Scene* scene );

  // ===============================================
  // Resource Management
  // ===============================================
private:
  std::unordered_map<std::string, GameResource*> _attachedResources;

public:
  void attach( GameResource* resource );

  void detach( GameResource* resource );

  GameResource* getResource( const std::string& name );

  std::vector<GameResource*> getResourcesWith( Scene* scope );

  std::vector<GameResource*> getAllResources();

  // ===============================================
  // Global messenger
  // ===============================================
private:
  Messenger* _globalMessenger;

public:
  Messenger* getGlobalMessenger() const;
};

// TEMPLATE DEFINITIONS

// ===============================================
// Object Management
// ===============================================

template <class T>
T* GameManager::getNodeTById( const long id ) {
  const auto nodeIt = _attachedNodes.find( id );
  if (nodeIt == _attachedNodes.end() ) return NULL;

  const auto node = nodeIt->second;
  if ( ALA_IS_INSTANCE_OF(node, T) ) {
    return static_cast<T *>(node);
  }
  return NULL;
}

template <class T>
T* GameManager::getNodeTByName( const std::string& name ) {
  for ( auto& pair : _attachedNodes ) {
    auto node = pair.second;
    if (node == NULL ) continue;
    if (node->getName() == name ) {
      if ( ALA_IS_INSTANCE_OF(node, T) ) {
        return static_cast<T *>(node);
      }
    }
  }
  return NULL;
}
}

#endif //__ALADDIN_CORE_GAME_MANAGER_H__
