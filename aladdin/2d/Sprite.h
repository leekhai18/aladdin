#ifndef __ALADDIN_2D_SPRITE_H__
#define __ALADDIN_2D_SPRITE_H__

#include "../core/Node.h"
#include "Texture.h"
#include "Rect.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1(Sprite, Node)
protected:
  Texture* _texture;
  Color _backColor;
  int _zOrder;
  Rect _srcRect;
public:
  Sprite(Scene* parentScene, Texture* texture = NULL, const std::string& name = "");
  Sprite(Scene* parentScene, const std::string& textureResourceName = "", const std::string& name = "");

  Texture* getTexture() const;
  void setTexture(Texture* texture);

  const Color& getBackColor()const;
  void setBackColor(const Color& color);

  Size getFrameSize() const;

  void setZOrder(int zOrder);
  int getZOrder() const;

  void render() override;
};
}

#endif //!__ALADDIN_2D_SPRITE_H__