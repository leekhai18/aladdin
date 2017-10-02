/*
 * Created by phuctm97 on Sep 30th 2017
 */

#ifndef __ALADDIN_CORE_VEC2_H__
#define __ALADDIN_CORE_VEC2_H__

#include "ClassMeta.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_0(Vec2)
private:
  float _x;
  float _y;

public:
  Vec2( const float x = 0, const float y = 0 );

  virtual ~Vec2();

  float getX() const;

  void setX( const float x );

  float getY() const;

  void setY( const float y );
};
}

#endif //!__ALADDIN_CORE_VEC2_H__