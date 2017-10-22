#include "ThrowableApplePrefab.h"

USING_NAMESPACE_ALA;

void ThrowableApplePrefab::doInstantiate( ala::GameObject* object ) {
  new SpriteRenderer( object, "throwable_apple.png" );
}
