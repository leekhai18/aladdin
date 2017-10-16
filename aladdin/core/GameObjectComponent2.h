#ifndef __ALADDIN_CORE_GAME_OBJECT_COMPONENT_H__
#define __ALADDIN_CORE_GAME_OBJECT_COMPONENT_H__

/*
 * Created by phuctm97 on Sep 27th 2017
 */

#include "ClassMeta.h"
#include "Initializable.h"
#include "Releasable.h"

NAMESPACE_ALA
{
class GameObject;

ALA_CLASS_HEADER_2(GameObjectComponent, ala::Initializable, ala::Releasable)
  // =====================================================
  // Basic
  // =====================================================
private:
  std::string _name;
  GameObject* _gameObject;
  bool _active;
  bool _selfInitialize;
  bool _toReleaseInNextFrame;

public:
  /**
   * \brief Create a component and attach it to game object
   * \param gameObject Target game object
   * \param name Component name
   */
  GameObjectComponent( GameObject* gameObject, const std::string& name = "" );

  virtual ~GameObjectComponent();

  const std::string& getName() const;

  GameObject* getGameObject() const;

  bool isActive() const;

  void setActive( const bool val );

  bool isSelfInitialize() const;

  void setSelfInitialize( const bool val );

  // ==================================================
  // Events
  // ==================================================
protected:
  /**
   * \brief Happen when component is initialized
   * \return true to continue initlization or false to stop it and crash the application
   */
  virtual void onInitialize();

  virtual bool onPreInitialize();

  /**
   * \brief Happen when component is updated
   * \param delta 
   */
  virtual void onUpdate( const float delta );

  virtual void onPreUpdate( const float delta );


  /**
   * \brief Happen when component is rendered
   */
  virtual void onRender();


  /**
   * \brief Happen when component is released
   */
  virtual void onRelease();

  virtual bool onPreRelease();

public:
  void initialize() override;

  void update( const float delta );

  void render();

  /**
   * \brief Release and destroy component, automatically removed from game object
   */
  void release() override;

  void releaseInNextFrame();

  // ===========================================================
  // Debug memory allocation
  // ===========================================================
public:
  static long TOTAL_COMPONENTS_CREATED;
  static long TOTAL_COMPONENTS_DELETED;
};
}

#endif //__ALADDIN_CORE_GAME_OBJECT_COMPONENT_H__
