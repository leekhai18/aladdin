#ifndef __ALADDIN_2D_TEXTURE_H__
#define __ALADDIN_2D_TEXTURE_H__

/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "2dInclude.h"
#include "Size.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1(Texture, ala::GameResource)
  // ======================================
  // Basic
  // ======================================
private:
  std::string _sourceFile;
  ala::Size _contentSize;
  ala::Color _transColor;

public:
  Texture( const std::string& name, const std::string& sourceFile, const ala::Color& transColor = ala::Color( 255, 0, 255 ), Scene* scope = NULL );

  virtual ~Texture();

  const std::string& getSourceFile() const;

  const ala::Color& getTransColor() const;

  const ala::Size& getContentSize() const;

  void setContentSize( const ala::Size& size );

protected:
  void onLoad() override;

  void onRelease() override;

  // ======================================
  // Platform specific
  // ======================================
private:
  LPDIRECT3DTEXTURE9 _directXTexture;

public:
  void setDirectXTexture( LPDIRECT3DTEXTURE9 directXTexture );

  LPDIRECT3DTEXTURE9 getDirectXTexture();
};
}

#endif //!__ALADDIN_2D_TEXTURE_H__
