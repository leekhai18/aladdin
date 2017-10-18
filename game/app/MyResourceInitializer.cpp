/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "MyResourceInitializer.h"
#include "../prefabs/BallPrefab.h"
#include "../prefabs/CameraPrefab.h"
#include "../prefabs/AladdinPrefab.h"
#include "../prefabs/BackgroundPrefab.h"

void MyResourceInitializer::run() {
	// Layer
	ala::GameManager::get()->addLayer("background");


  // Textures
  new ala::Sprite( "ball.png", "textures/ball.png" );
  new ala::Sprite( "sprites.png", "textures/sprites.png" );
  new ala::Animation( "sprites.animation", "animations/sprites.animation" );

  new ala::Sprite("aladdin.png", "textures/aladdin.png");
  new ala::Animation("aladdin.animation", "animations/aladdin.animation");

  new ala::Sprite("background.png", "textures/background.png");

  // Audio
  new ala::AudioClip( "wow.wav", "audio/sfx/wow.wav" );

  // Prefabs
  new AladdinPrefab();
  new BallPrefab();
  new CameraPrefab();
  new BackgroundPrefab();
}
