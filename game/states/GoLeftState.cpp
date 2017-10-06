#include "GoLeftState.h"
#include "core/GameManager.h"
#include "GoUpState.h"
#include "2d/Animator.h"

GoLeftState::GoLeftState ( ala::GameObject* gameObject)
  :IState ( gameObject )
{
}

ala::IState* GoLeftState::checkTransition ( )
{
  auto transform = getGameObject()->getTransform (  );

  if(transform->getPositionX (  ) <= -ala::GameManager::get (  )->getScreenWidth (  )/2)
  {
    auto animator = getGameObject()->getComponentT< ala::Animator>();
    animator->setAction("Back");
    return new GoUpState(getGameObject (  ));
  }
  else
  {
    return NULL;
  }
}

void GoLeftState::onUpdate ( const float dt )
{
  auto position = getGameObject()->getTransform()->getPosition (  );
  position.setX(position.getX() - 10);
  getGameObject()->getTransform()->setPosition(position);
}