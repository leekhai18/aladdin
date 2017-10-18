#include "BackgroundPrefab.h"

void BackgroundPrefab::doInstantiate(ala::GameObject * object)
{
	auto spriteRenderer = new ala::SpriteRenderer(object, "background.png");
	
	object->setLayer("background");
	auto transform = object->getTransform();
	auto frameSize = spriteRenderer->getFrameSize();

	transform->setPosition(ala::Vec2(frameSize.getWidth() / 2, frameSize.getHeight() / 2));
}
