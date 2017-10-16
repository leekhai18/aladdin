/*
 * Created by phuctm97 on Sep 30th 2017
 */

#ifndef __ALADDIN_CORE_SCENE_H__
#define __ALADDIN_CORE_SCENE_H__

/*
* Created by phuctm97 on Sep 27th 2017
*/

#include "Node.h"

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
  std::unordered_map<long, Node*> _nodes;
  bool _nodeInLocking;
  std::vector<Node*> _nodesToAddInNextFrame;
  std::vector<Node*> _nodesToRemoveInNextFrame;

public:
  Node* getNode( const long id );

  /**
   * \brief Attach game object to scene, this will not change game object's parent, you should not call this method directly
   * \param Node Game object to attach
   */
  void addNode(Node* node);

  void addNodeInNextFrame(Node* node);

  /**
   * \brief Detach game object from scene, this will not change game object's parent or release it, you should not call this method directly
   * \param Node Game object to detach
   */
  void removeNode(Node* node);

  void removeNodeInNextFrame(Node* node);

private:
  void lockNodes();

  void unlockNodes();

  void updateAddAndRemoveNodes();

  void doAddNode(Node* node);

  void doRemoveNode(Node* node );

  // =============================================
  // Debug memory allocation
  // =============================================
public:
  static long TOTAL_SCENES_CREATED;
  static long TOTAL_SCENES_DELETED;
};
}

#endif //!__ALADDIN_CORE_SCENE_H__
