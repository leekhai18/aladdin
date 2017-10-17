#include "AladdinPrefab.h"

void AladdinPrefab::doInstantiate( ala::GameObject* object ) {
	object->getTransform()->setPosition(ala::GameManager::get()->getScreenWidth() / 2, ala::GameManager::get()->getScreenHeight() / 2);

	new ala::SpriteRenderer(object, "aladdin.png");
	new ala::Animator(object, "idle1", "aladdin.animation");
	auto stateManager = new ala::StateManager(object, "stand_right");
	auto animator = object->getComponentT<ala::Animator>();
	// State Stand
	new ala::State(stateManager, "stand_right",
		[=] {
		animator->setAction("idle1");
	}, NULL, NULL);
	new ala::State(stateManager, "stand_left",
		[=] {
		animator->setAction("idle1");
	}, NULL, NULL);

	// State Go
	new ala::State(stateManager, "go_right",
		[=] {
		animator->setAction("run_1");
		object->getTransform()->setScaleX(1);
	},
		[=](float dt) {
		if (animator->getAction() == "run_1" && !animator->isPlaying())
			animator->setAction("run_2");
		auto position = object->getTransform()->getPosition();
		position.setX(position.getX() + 120 * dt);
		object->getTransform()->setPosition(position);
	}, NULL);
	new ala::State(stateManager, "go_left",
		[=] {
		animator->setAction("run_1");
		object->getTransform()->setScaleX(-1);
	},
		[=](float dt) {
		if (animator->getAction() == "run_1" && !animator->isPlaying())
			animator->setAction("run_2");
		auto position = object->getTransform()->getPosition();
		position.setX(position.getX() - 120 * dt);
		object->getTransform()->setPosition(position);
	}, NULL);

	// State Sit
	new ala::State(stateManager, "sit",
		[=] {
		animator->setAction("sit");
	}, NULL, NULL);

	// State Jump
	new ala::State(stateManager,"jump_up",
		[=] {
		animator->setAction("jumpnup");
	}, 
		[=](float dt) {
		if (animator->getAction() == "jumpnup" && animator->isPlaying())
		{
			auto position = object->getTransform()->getPosition();
			position.setY(position.getY() + 100 * 0.03);
			object->getTransform()->setPosition(position);
		}
	}, NULL);
	new ala::State(stateManager, "jump_down",
		[=] {
		animator->setAction("jumpndown");
	},
		[=](float dt) {
		if (animator->getAction() == "jumpndown" && animator->isPlaying())
		{
			auto position = object->getTransform()->getPosition();
			position.setY(position.getY() - 101 * 0.03);
			object->getTransform()->setPosition(position);
		}
	}, NULL);

	// State Look Up
	new ala::State(stateManager,"look_up",
		[=] {
		animator->setAction("lookup");
	}, NULL, NULL);

	new ala::StateTransition(stateManager, "stand_right", "go_right",
		[] {
		return ala::Input::get()->getKeyDown(ALA_KEY_RIGHT_ARROW);
	});
	new ala::StateTransition(stateManager, "stand_right", "go_left",
		[] {
		return ala::Input::get()->getKeyDown(ALA_KEY_LEFT_ARROW);
	});
	new ala::StateTransition(stateManager, "go_right", "go_left",
		[] {
		return ala::Input::get()->getKeyDown(ALA_KEY_LEFT_ARROW);
	});
	new ala::StateTransition(stateManager, "go_right", "stand_right",
		[] {
		return ala::Input::get()->getKeyUp(ALA_KEY_RIGHT_ARROW);
	});
	new ala::StateTransition(stateManager, "stand_left", "go_left",
		[] {
		return ala::Input::get()->getKeyDown(ALA_KEY_LEFT_ARROW);
	});
	new ala::StateTransition(stateManager, "stand_left", "go_right",
		[] {
		return ala::Input::get()->getKeyDown(ALA_KEY_RIGHT_ARROW);
	});
	new ala::StateTransition(stateManager, "go_left", "stand_left",
		[] {
		return ala::Input::get()->getKeyUp(ALA_KEY_LEFT_ARROW);
	});
	new ala::StateTransition(stateManager, "stand_left", "sit",
		[] {
		return ala::Input::get()->getKeyDown(ALA_KEY_DOWN_ARROW);
	});
	new ala::StateTransition(stateManager, "stand_right", "sit",
		[] {
		return ala::Input::get()->getKeyDown(ALA_KEY_DOWN_ARROW);
	});
	new ala::StateTransition(stateManager, "sit", "stand_left",
		[] {
		return ala::Input::get()->getKeyUp(ALA_KEY_DOWN_ARROW);
	});
	new ala::StateTransition(stateManager, "sit", "stand_right",
		[] {
		return ala::Input::get()->getKeyUp(ALA_KEY_DOWN_ARROW);
	});
	new ala::StateTransition(stateManager,"stand_right","jump_up",
		[] {
		return ala::Input::get()->getKeyDown(ALA_KEY_D);
	});
	new ala::StateTransition(stateManager, "stand_left", "jump_up",
		[] {
		return ala::Input::get()->getKeyDown(ALA_KEY_D);
	});
	new ala::StateTransition(stateManager, "jump_up", "jump_down",
		[=] {
		return animator->getAction() == "jumpnup"&& !animator->isPlaying();
	});
	new ala::StateTransition(stateManager, "jump_down", "stand_left",
		[=] {
		return animator->getAction() == "jumpndown" && !animator->isPlaying();
	});
	new ala::StateTransition(stateManager, "jump_down", "stand_right",
		[=] {
		return animator->getAction() == "jumpndown" && !animator->isPlaying();
	});
	new ala::StateTransition(stateManager, "stand_right", "look_up",
		[] {
		return ala::Input::get()->getKeyDown(ALA_KEY_UP_ARROW);
	});
	new ala::StateTransition(stateManager, "stand_left", "look_up",
		[] {
		return ala::Input::get()->getKeyDown(ALA_KEY_UP_ARROW);
	});
	new ala::StateTransition(stateManager, "look_up", "stand_right",
		[] {
		return ala::Input::get()->getKeyUp(ALA_KEY_UP_ARROW);
	});
	new ala::StateTransition(stateManager, "look_up", "stand_left",
		[] {
		return ala::Input::get()->getKeyUp(ALA_KEY_UP_ARROW);
	});
}
