/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "Texture.h"
#include "Graphics.h"

NAMESPACE_ALA
{
ALA_CLASS_SOURCE_1(ala::Texture, ala::GameResource)

Texture::Texture( const std::string& name, const std::string& sourceFile, const ala::Color& transColor, Scene* scope )
  : GameResource( name, scope ),
    _sourceFile( sourceFile ),
    _contentSize( 0, 0 ),
    _transColor( transColor ),
    _directXTexture( 0 ) {}

Texture::~Texture() {}

const std::string& Texture::getSourceFile() const {
  return _sourceFile;
}

const ala::Color& Texture::getTransColor() const {
  return _transColor;
}

const ala::Size& Texture::getContentSize() const {
  return _contentSize;
}

void Texture::setContentSize( const Size& size ) {
  _contentSize = size;
}

void Texture::onLoad() {
  Graphics::get()->loadTexture( this );
  ALA_ASSERT( _directXTexture != 0);
}

void Texture::onRelease() {
  if ( _directXTexture ) {
    _directXTexture->Release();
  }
}

void Texture::setDirectXTexture( LPDIRECT3DTEXTURE9 directXTexture ) {
  _directXTexture = directXTexture;
}

LPDIRECT3DTEXTURE9 Texture::getDirectXTexture() {
  return _directXTexture;
}
}
