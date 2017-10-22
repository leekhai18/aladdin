#ifndef __ALADDIN_MOVEMENT_H__
#define __ALADDIN_MOVEMENT_H__

#include <aladdin.h>

class VectorBasedMovement : public ala::GameObjectComponent {
private:
  ala::Vec2 _vector;

public:
  VectorBasedMovement( ala::GameObject* gameObject, const std::string& name = "" );

  void setVector( const ala::Vec2& vector );

  void setVectorX( const float x );

  void setVectorY( const float y );

  const ala::Vec2& getVector() const;

protected:
  void onUpdate( const float delta ) override;
};

#endif //!__ALADDIN_MOVEMENT_H__
