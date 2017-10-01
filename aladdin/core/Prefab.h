/*
 * Created by phuctm97 on Sep 30th 2017
 */

#ifndef __ALADDIN_CORE_PREFAB_H__
#define __ALADDIN_CORE_PREFAB_H__

#include "GameObject.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_0(Prefab)
private:
  std::string _name;
  bool _destructed;
  bool _released;

public:
  Prefab( const std::string& name );

  virtual ~Prefab();

  const std::string& getName() const;

  GameObject* instantiate();

protected:
  virtual GameObject* doInstantiate();

public:
  void release();

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
