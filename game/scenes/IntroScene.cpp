/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "IntroScene.h"
#include "../nodes/MyAladdin.h"

IntroScene::IntroScene() : _logger( "IntroScene" ) {}

void IntroScene::onPreInitialize() {
  new MyAladdin(this);
}

void IntroScene::onPreRelease() {}
