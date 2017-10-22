#ifndef __THROWABLE_APPLE_PREFAB_H__
#define __THROWABLE_APPLE_PREFAB_H__

#include <aladdin.h>

class ThrowableApplePrefab : public ala::Prefab {

public:
  ThrowableApplePrefab() : Prefab( "Throwable Apple" ) {}

protected:
  void doInstantiate( ala::GameObject* object ) override;
};

#endif //!__THROWABLE_APPLE_PREFAB_H__
