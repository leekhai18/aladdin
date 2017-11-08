/*
 * Created by phuctm97 on Sep 30th 2017
 */

#ifndef __ALADDIN_CORE_SCENE_H__
#define __ALADDIN_CORE_SCENE_H__

/*
* Created by phuctm97 on Sep 27th 2017
*/

#include "GameObject.h"
#include "QuadNode.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_2(Scene, ala::Initializable, ala::Releasable)

  // ================================================
  // Basic
  // ================================================
private:
  bool _toReleaseInNextFrame;

public:
  /**
   * \brief Create a scene, this will not be managed unless you attach to GameManager by call replaceScene
   */
  Scene();

  virtual ~Scene();

  // ==================================================
  // Events
  // ==================================================
public:
  void initialize() override;

protected:

  /**
   * \brief Add Default Objects and Scene Resources here, they will be init right after this function return
   */
  virtual void onPreInitialize();

  /**
  * \brief Add special Logic happen after initlization, every object and component in scene has been initialized
  * Object and Component added to scene there will be not automatically init, so you have to init them manually
  */
  virtual void onPostInitialize();

public:
  void update( const float delta );

protected:

  /**
   * \brief Happen before scene, its objects and components were updated
   * \param delta 
   */
  virtual void onPreUpdate( const float delta );


  /**
   * \brief Happen after scene, its objects and components were updated
   */
  virtual void onPostUpdate( const float delta );

public:
  void render();

protected:
  /**
   * \brief Happen before scene, its objects and components were rendered
   */
  virtual void onPreRender();


  /**
   * \brief Happen after scene, its objects and components were rendered
   */
  virtual void onPostRender();

public:
  /**
   * \brief Release and destroy scene, this will not change running scene, you should not call this method directly
   */
  void release() override;

  void releaseInNextFrame();

protected:

  /**
   * \brief Happen before scene, its objects and components were released
   */
  virtual void onPreRelease();


  /**
   * \brief Happen after scene, its objects and components were released and destroyed
   */
  virtual void onPostRelease();

  // ==================================================
  // Objects Management
  // ==================================================
private:
  std::unordered_map<long, GameObject*> _gameObjects;
  std::unordered_map<long, QuadNode*> _quadNodes;

  bool _gameObjectInLocking;
  std::vector<GameObject*> _gameObjectsToAddInNextFrame;
  std::vector<GameObject*> _gameObjectsToRemoveInNextFrame;

public:
  GameObject* getGameObject( const long id );

  /**
   * \brief Attach game object to scene, this will not change game object's parent, you should not call this method directly
   * \param gameObject Game object to attach
   */
  void addGameObject( GameObject* gameObject );

  void addGameObjectInNextFrame( GameObject* gameObject );

  /**
   * \brief Detach game object from scene, this will not change game object's parent or release it, you should not call this method directly
   * \param gameObject Game object to detach
   */
  void removeGameObject( GameObject* gameObject );

  void removeGameObjectInNextFrame( GameObject* gameObject );

private:
  void lockGameObjects();

  void unlockGameObjects();

  void updateAddAndRemoveGameObjects();

  void doAddGameObject( GameObject* gameObject );

  void doRemoveGameObject( GameObject* gameObject );

  // =============================================
  // Debug memory allocation
  // =============================================
public:
  static long TOTAL_SCENES_CREATED;
  static long TOTAL_SCENES_DELETED;
};
}

#endif //!__ALADDIN_CORE_SCENE_H__
