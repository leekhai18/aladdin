/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "MyResourceInitializer.h"
#include "../prefabs/CameraPrefab.h"
#include "../prefabs/AladdinPrefab.h"
#include "../prefabs/ThrowableApplePrefab.h"

void MyResourceInitializer::run() {
  // Textures
  new ala::Sprite( "aladdin.png", "textures/playable_characters/aladdin.png" );
  new ala::Sprite( "throwable_apple.png", "textures/miscellaneous/throwable_apple.png" );

  // Animations
  new ala::Animation( "aladdin.animation", "animations/playable_characters/aladdin.animation" );

  // Audio
  new ala::AudioClip( "wow.wav", "audio/sfx/wow.wav" );

  // Prefabs
  new CameraPrefab();
  new AladdinPrefab();
  new ThrowableApplePrefab();
}
