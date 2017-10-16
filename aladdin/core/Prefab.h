/*
 * Created by phuctm97 on Sep 30th 2017
 */

#ifndef __ALADDIN_CORE_PREFAB_H__
#define __ALADDIN_CORE_PREFAB_H__

#include "Node.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1(Prefab, ala::Releasable)
private:
  std::string _name;

public:
  Prefab( const std::string& name );

  virtual ~Prefab();

  const std::string& getName() const;

  GameObject* instantiate( const std::string& name = "" );

  GameObject* instantiate( Scene* scene, const std::string& name = "" );

  GameObject* instantiate( GameObject* parentObject, const std::string& name = "" );

protected:
  virtual void doInstantiate( GameObject* object ) = 0;

public:
  void release() override;

protected:
  virtual void onRelease();

  // =============================================
  // Debug memory allocation
  // =============================================
public:
  static long TOTAL_PREFABS_CREATED;
  static long TOTAL_PREFABS_DELETED;
};
}

#endif //!__ALADDIN_CORE_PREFAB_H__
