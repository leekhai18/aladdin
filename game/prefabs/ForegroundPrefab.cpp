#include "ForegroundPrefab.h"

void ForegroundPrefab::doInstantiate(ala::GameObject * object)
{
	auto spriteRenderer = new ala::SpriteRenderer(object, "foreground.png");

	object->setLayer("Foreground");
	auto transform = object->getTransform();
	auto frameSize = spriteRenderer->getFrameSize();

	transform->setPosition(ala::Vec2(frameSize.getWidth() / 2, frameSize.getHeight() / 2));
}
