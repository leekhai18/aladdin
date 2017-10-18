#include "CameraController.h"

CameraController::CameraController(ala::GameObject * gameObject, const std::string & name)
	:GameObjectComponent(gameObject, name)
{
}

void CameraController::onUpdate(const float delta)
{
	if (ala::Input::get()->getKey(ALA_KEY_LEFT_ARROW))
	{
		auto transform = getGameObject()->getTransform();
		transform->setPositionX(transform->getPositionX() - 10);
	}
	else if (ala::Input::get()->getKey(ALA_KEY_RIGHT_ARROW))
	{
		auto transform = getGameObject()->getTransform();
		transform->setPositionX(transform->getPositionX() + 10);

	}
}
