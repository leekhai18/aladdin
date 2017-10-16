#ifndef __MY_ALADDIN_H__
#define __MY_ALADDIN_H__

#include "2d/Sprite.h"
#include "2d/Animation.h"

class MyAladdin: ala::Sprite
{
public:
  MyAladdin(ala::Scene* parentScene, const std::string& name = "");
protected:
  void initialize() override;
  void update(const float dt) override;
  float _elapsedTime;
  float _timeToNextFrame;

  std::vector<ala::Rect>::iterator _frameIterator;
  std::vector<ala::Rect> _frames;
  ala::Animation* _animation;
};

#endif //!__ALADDIN_H__