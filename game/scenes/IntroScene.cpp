/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "IntroScene.h"

IntroScene::IntroScene() : _logger( "IntroScene" ) {}

void IntroScene::onPreInitialize() {
  ala::GameManager::get()->getPrefab( "Camera" )->instantiate();
  ala::GameManager::get()->getPrefab( "Aladdin" )->instantiate();
}

void IntroScene::onPreRelease() {}
