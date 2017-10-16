#include "MyAladdin.h"

MyAladdin::MyAladdin ( ala::Scene* parentScene, const std::string& name )
  : Sprite(parentScene, static_cast < ala::Texture* > ( ala::GameManager::get ( ) -> getResource ( "aladdin.png" ) ), name),
    _elapsedTime ( 0 )
{
}

void MyAladdin::initialize ( )
{
  Sprite::initialize();
  _animation = static_cast < ala::Animation* > (ala::GameManager::get()->getResource("aladdin.animation"));
  _frames = _animation->getAction("idle1")->getFrames();
  _timeToNextFrame = _animation->getAction("idle1")->getInterval();
  _frameIterator = _frames.begin();
  _srcRect = *_frameIterator;
  _position = ala::Vec2(ala::GameManager::get()->getScreenWidth() / 2, ala::GameManager::get()->getScreenHeight() / 2);
}

void MyAladdin::update ( const float dt )
{
  Sprite::update(dt);
  _elapsedTime += dt;
  if(_elapsedTime >= _timeToNextFrame)
  {
    ++_frameIterator;
    if(_frameIterator == _frames.end (  ))
    {
      _frameIterator = _frames.begin();
    }
    _srcRect = *_frameIterator;
    _elapsedTime = 0;
  }

}
