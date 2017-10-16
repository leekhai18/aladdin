#ifndef __ALADDIN_CORE_NODE_H__
#define __ALADDIN_CORE_NODE_H__

/*
* Created on Sep 27th 2017
*/


#include "Messenger.h"
#include "Initializable.h"
#include "Vec2.h"
#include "Mat4.h"

NAMESPACE_ALA
{
class Scene;

ALA_CLASS_HEADER_2(Node, ala::Initializable, ala::Releasable)
// =========================================================================
// Basic
// =========================================================================
private:
  long _id;
  std::string _name;
  Scene* _parentScene;
  bool _active;
  bool _selfInitialize;
  bool _toReleaseInNextFrame;

public:
  /**
  * \brief Create a game object, attach to game manager and attach to parent scene
  */
  Node(Scene* parentScene, const std::string& name = "");

  virtual ~Node();

  long getId() const;

  const std::string& getName() const;

  Scene* getParentScene() const;

  bool isActive() const;

  void setActive(const bool val);

  bool isSelfInitialize() const;

  void setSelfInitialize(const bool val);

  // =========================================================
  // Transform
  // =========================================================
protected:
  Vec2 _position;
  Vec2 _scale;
  float _rotation;
  Vec2 _origin;

public:
  const Vec2& getPosition() const;

  float getPositionX() const;

  float getPositionY() const;

  void setPosition(const Vec2& position);

  void setPosition(const float x, const float y);

  void setPositionX(const float x);

  void setPositionY(const float y);

  const Vec2& getScale() const;

  void setScale(const Vec2& scale);

  void setScaleX(const float x);

  void setScaleY(const float y);

  void setScale(const float scale);

  float getRotation() const;

  void setRotation(const float rotation);

  Mat4 getTransformationMatrix() const;

  // =========================================================
  // Events
  // =========================================================
public:
  void initialize() override;

  virtual void update(const float delta);

  virtual void render();

  /**
  * \brief Release and destroy game object, automatically removed from parent scene or "parent object" and detached from game manager
  */
  void release() override;

  void releaseInNextFrame();

  // ===========================================================
  // Debug memory allocation
  // ===========================================================
public:
  static long TOTAL_NODES_CREATED;
  static long TOTAL_NODES_DELETED;
};
}


#endif //!__ALADDIN_CORE_NODE_H__
