﻿#include "Animation.h"

#include "../pugixml/pugixml.hpp"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1(ala::Animation, ala::GameResource)

void Animation::onLoad ( )
{
  pugi::xml_document _animationFile;
  pugi::xml_parse_result result = _animationFile.load_file(_sourceFile.c_str (  ));

  ALA_ASSERT(result);

  auto atlasNode = _animationFile.child("TextureAtlas");

  auto actionNodes = atlasNode.children();

  for(auto action: actionNodes)
  {
    const std::string actionName = action.attribute("actionName").as_string();

    auto frameNodes = action.children("Rect");

    std::vector<Rect> frames;

    for(auto frame: frameNodes)
    {
      Rect rect;
      rect.setTopLeft(Vec2(frame.attribute("x").as_int(), frame.attribute("y").as_int()));
      rect.setSize(Size(frame.attribute("width").as_int(), frame.attribute("height").as_int()));
      rect.setTopLeft(Vec2(rect.getTopLeft().getX(), rect.getTopLeft().getY()));
      frames.push_back(rect);
    }

    const auto animationAction = AnimationAction(frames, actionName, action.attribute("interval").as_float(), action.attribute("isLoop").as_bool());

    _frames[actionName] = animationAction;
  }
}

void Animation::onRelease ( )
{
}

Animation::Animation ( const std::string& name, const std::string& sourceFile, Scene* scope )
  : GameResource ( name, scope )
{
  _sourceFile = sourceFile;
}

AnimationAction* Animation::getAction ( const std::string& actionName )
{
  return &_frames[actionName];
}

Animation::~Animation ( )
{
}
}
