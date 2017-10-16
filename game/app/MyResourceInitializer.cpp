/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "MyResourceInitializer.h"
#include "2d/Animation.h"

void MyResourceInitializer::run() {
  // Textures
  new ala::Texture( "ball.png", "textures/ball.png" );
  new ala::Texture( "sprites.png", "textures/sprites.png" );

  new ala::Texture("aladdin.png", "textures/aladdin.png");

  new ala::Animation("aladdin.animation", "animations/aladdin.animation");

  // Audio
  new ala::AudioClip( "wow.wav", "audio/sfx/wow.wav" );

}
