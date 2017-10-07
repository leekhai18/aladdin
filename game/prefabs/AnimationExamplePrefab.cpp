﻿#include "AnimationExamplePrefab.h"
#include "../scripts/BallController.h"
#include "core/StateManager.h"
#include "../states/GoRightState.h"
#include "2d/Animator.h"

void AnimationExamplePrefab::doInstantiate(ala::GameObject* object) {
  new ala::SpriteRenderer(object, "sprites.png");
  new ala::Animator(object, "Right", "sprites.animation", 1.f / 12);
  new BallController(object);
  new ala::StateManager(object, new GoRightState(object));
}