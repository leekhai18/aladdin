#include "AladdinPrefab.h"
#include "../scripts/VectorBasedMovement.h"

void AladdinPrefab::doInstantiate( ala::GameObject* object ) {
  new ala::SpriteRenderer( object, "aladdin.png" );
  auto animator = new ala::Animator( object, "idle_1", "aladdin.animation" );
  auto stateManager = new ala::StateManager( object, "stand_right" );
  auto movement = new VectorBasedMovement( object );
  auto transform = object->getTransform();

  // Start position
  transform->setPosition( ala::GameManager::get()->getScreenWidth() / 2, ala::GameManager::get()->getScreenHeight() / 2 );

  // State Stand
  new ala::State( stateManager, "stand_right",
                  [=] {
                  animator->setAction( "idle_1" );
                  transform->setScaleX( 1 );
                  movement->setVectorX( 0 );
                }, NULL, NULL );
  new ala::State( stateManager, "stand_left",
                  [=] {
                  animator->setAction( "idle_1" );
                  transform->setScaleX( -1 );
                  movement->setVectorX( 0 );
                }, NULL, NULL );


  // State Go
  float goSpeed = 90;

  new ala::State( stateManager, "go_right",
                  [=] {
                  animator->setAction( "run_1" );
                  transform->setScaleX( 1 );
                  movement->setVectorX( goSpeed );
                },
                  [=]( float dt ) {
                  if ( animator->getAction() == "run_1" && !animator->isPlaying() )
                    animator->setAction( "run_2" );
                }, NULL );

  new ala::State( stateManager, "go_left",
                  [=] {
                  animator->setAction( "run_1" );
                  transform->setScaleX( -1 );
                  movement->setVectorX( -goSpeed );
                },
                  [=]( float dt ) {
                  auto position = object->getTransform()->getPosition();
                  position.setX( position.getX() - 100 * dt );
                  object->getTransform()->setPosition( position );
                },
                  NULL );
  new ala::State(stateManager, "jump",
				[=] {
				auto animator = object->getComponentT<ala::Animator>();
				animator->setAction("jumpnfall");
				object->getTransform()->setScaleY(1);
			},
				[=](float dt) {
				auto position = object->getTransform()->getPosition();
				position.setY(position.getY() + 100 * dt);
				object->getTransform()->setPosition(position);
			},
				NULL);
  new ala::State(stateManager, "fall",
	  [=] {
	  auto animator = object->getComponentT<ala::Animator>();
	  animator->setAction("falltoground");
	  object->getTransform()->setScaleY(1);
  },
	  [=](float dt) {
	  auto position = object->getTransform()->getPosition();
	  position.setY(position.getY() - 100 * dt);
	  object->getTransform()->setPosition(position);
  },
	NULL);
  new ala::State(stateManager, "sit",
	  [=] {
	  auto animator = object->getComponentT<ala::Animator>();
	  animator->setAction("sit");
	  object->getTransform()->setScaleY(1);
  }, NULL, NULL);
                  if ( animator->getAction() == "run_1" && !animator->isPlaying() )
                    animator->setAction( "run_2" );
                }, NULL );

  new ala::StateTransition(stateManager, "stand-left", "jump", [] {
	  return ala::Input::get()->getKeyDown(ALA_KEY_UP_ARROW);
  });
  new ala::StateTransition(stateManager, "stand-right", "jump", [] {
	  return ala::Input::get()->getKeyDown(ALA_KEY_UP_ARROW);
  });
  new ala::StateTransition(stateManager, "jump", "fall", [=] {
	  auto position = object->getTransform()->getPosition();
	  if (position.getY() > (ala::GameManager::get()->getScreenHeight() / 2) + 50)
		  return true;
	  return false;
  });
  new ala::StateTransition(stateManager, "fall", "stand-right", [=] {
	  auto position = object->getTransform()->getPosition();
	  if (position.getY() > ala::GameManager::get()->getScreenHeight() / 2)
		return false;
	  return true;
  });
  new ala::StateTransition(stateManager, "fall", "stand-left", [=] {
	  auto position = object->getTransform()->getPosition();
	  if (position.getY() > ala::GameManager::get()->getScreenHeight() / 2)
		  return false;
	  return true;
  });
  new ala::StateTransition(stateManager, "stand-left", "sit", [] {
	  return ala::Input::get()->getKeyDown(ALA_KEY_DOWN_ARROW);
  });
  new ala::StateTransition(stateManager, "stand-right", "sit", [] {
	  return ala::Input::get()->getKeyDown(ALA_KEY_DOWN_ARROW);
  });
  new ala::StateTransition(stateManager, "sit", "stand-right", [] {
	  return ala::Input::get()->getKeyUp(ALA_KEY_DOWN_ARROW);
  });
  new ala::StateTransition(stateManager, "sit", "stand-left", [] {
	  return ala::Input::get()->getKeyUp(ALA_KEY_DOWN_ARROW);
  });

  new ala::StateTransition( stateManager, "go-left", "go-right", [] {
  // State Sit
  new ala::State( stateManager, "sit_left",
                  [=] {
                  animator->setAction( "sit" );
                  transform->setScaleX( -1 );
                  movement->setVectorX( 0 );
                }, NULL, NULL );
  new ala::State( stateManager, "sit_right",
                  [=] {
                  animator->setAction( "sit" );
                  transform->setScaleX( 1 );
                  movement->setVectorX( 0 );
                }, NULL, NULL );

  // State Throw
  new ala::State( stateManager, "throw_right",
                  [=] {
                  animator->setAction( "throw" );
                  transform->setScaleX( 1 );
                  movement->setVectorX( 0 );
                }, NULL, NULL );
  new ala::State( stateManager, "throw_left",
                  [=] {
                  animator->setAction( "throw" );
                  transform->setScaleX( -1 );
                  movement->setVectorX( 0 );
                }, NULL, NULL );

  new ala::StateTransition( stateManager, "stand_right", "go_right",
                            [] {
                            return ala::Input::get()->getKeyDown( ALA_KEY_RIGHT_ARROW );
                          } );
  new ala::StateTransition( stateManager, "stand_right", "go_left",
                            [] {
                            return ala::Input::get()->getKeyDown( ALA_KEY_LEFT_ARROW );
                          } );
  new ala::StateTransition( stateManager, "go_right", "go_left",
                            [] {
                            return ala::Input::get()->getKeyDown( ALA_KEY_LEFT_ARROW );
                          } );
  new ala::StateTransition( stateManager, "go_right", "stand_right",
                            [] {
                            return ala::Input::get()->getKeyUp( ALA_KEY_RIGHT_ARROW );
                          } );
  new ala::StateTransition( stateManager, "stand_left", "go_left",
                            [] {
                            return ala::Input::get()->getKeyDown( ALA_KEY_LEFT_ARROW );
                          } );
  new ala::StateTransition( stateManager, "stand_left", "go_right",
                            [] {
                            return ala::Input::get()->getKeyDown( ALA_KEY_RIGHT_ARROW );
                          } );
  new ala::StateTransition( stateManager, "go_left", "stand_left",
                            [] {
                            return ala::Input::get()->getKeyUp( ALA_KEY_LEFT_ARROW );
                          } );
  new ala::StateTransition( stateManager, "stand_left", "sit_left",
                            [] {
                            return ala::Input::get()->getKeyDown( ALA_KEY_DOWN_ARROW );
                          } );
  new ala::StateTransition( stateManager, "stand_right", "sit_right",
                            [] {
                            return ala::Input::get()->getKeyDown( ALA_KEY_DOWN_ARROW );
                          } );
  new ala::StateTransition( stateManager, "sit_left", "stand_left",
                            [] {
                            return ala::Input::get()->getKeyUp( ALA_KEY_DOWN_ARROW );
                          } );
  new ala::StateTransition( stateManager, "sit_right", "stand_right",
                            [] {
                            return ala::Input::get()->getKeyUp( ALA_KEY_DOWN_ARROW );
                          } );
  new ala::StateTransition( stateManager, "throw_right", "stand_right",
                            [=] {
                            return animator->getAction() == "throw" && !animator->isPlaying();
                          } );
  new ala::StateTransition( stateManager, "stand_right", "throw_right",
                            [] {
                            return ala::Input::get()->getKeyDown( ALA_KEY_A );
                          } );
  new ala::StateTransition( stateManager, "throw_left", "stand_left",
                            [=] {
                            return animator->getAction() == "throw" && !animator->isPlaying();
                          } );
  new ala::StateTransition( stateManager, "stand_left", "throw_left",
                            [] {
                            return ala::Input::get()->getKeyDown( ALA_KEY_A );
                          } );
}
