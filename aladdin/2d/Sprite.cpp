#include "Sprite.h"
#include "Graphics.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1 ( Sprite, Node )

Sprite::Sprite ( Scene* parentScene, Texture* texture, const std::string& name )
  :Node ( parentScene, name ),
  _texture(texture),
  _backColor ( 255,255,255 ),
  _zOrder ( 0 )
{
  _srcRect.setTopLeft(Vec2(0.f, 0.f));
  _srcRect.setSize(_texture->getContentSize());
}

Sprite::Sprite ( Scene* parentScene, const std::string& textureResourceName, const std::string& name )
  :Node(parentScene, name),
  _backColor ( 255,255,255 ),
  _zOrder ( 0 )
{
  _texture = static_cast<Texture*>(GameManager::get (  )->getResource(textureResourceName));
  _srcRect.setTopLeft(Vec2(0.f, 0.f));
  _srcRect.setSize(_texture->getContentSize());
}

Texture* Sprite::getTexture ( ) const
{
  return _texture;
}

void Sprite::setTexture ( Texture* texture )
{
  _texture = texture;
}

const Color& Sprite::getBackColor ( ) const
{
  return _backColor;
}

void Sprite::setBackColor ( const Color& color )
{
  _backColor = color;
}

Size Sprite::getFrameSize ( ) const
{
  return Size(_srcRect.getSize().getWidth()* _scale.getX(), _srcRect.getSize().getHeight()* _scale.getY());
}

void Sprite::setZOrder ( const int zOrder )
{
  _zOrder = zOrder;
}

int Sprite::getZOrder ( ) const
{
  return _zOrder;
}

void Sprite::render ( )
{
  if ((!isInitialized()) || isReleasing() || isReleased()) return;

  Graphics::get()->drawTexture(_texture, _origin, getTransformationMatrix (  ), _backColor, _srcRect, _zOrder);
}
}
