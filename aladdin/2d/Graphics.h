#ifndef __ALADDIN_2D_GRAPHICS_2D_H__
#define __ALADDIN_2D_GRAPHICS_2D_H__

/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "2dInclude.h"
#include "Rect.h"

NAMESPACE_ALA
{
  class Texture;

ALA_CLASS_HEADER_2(Graphics, ala::Initializable, ala::Releasable)
  // ==========================================
  // Basic
  // ==========================================
  friend class Application;

private:
  static Graphics* __instance;
  Logger _logger;

public:
  Graphics();

  virtual ~Graphics();

  static Graphics* get();

  void initialize() override;

  void release() override;

  // ==========================================
  // Platform specific
  // ==========================================
private:
  HINSTANCE _hInstance;
  HWND _hWnd;
  UINT _screenWidth;
  UINT _screenHeight;
  IDirect3D9* _directX;
  IDirect3DDevice9* _directXDevice;
  LPD3DXSPRITE _directXSprite;

  D3DXMATRIX _projectionMatrix;
  D3DXMATRIX _worldMatrix;
  D3DXMATRIX _viewMatrix;
public:
  void initDirectX();

  void releaseDirectX();

  bool beginRendering();

  void endRendering();

  void loadTexture(Texture* texture) const;

  void drawTexture(Texture* texture, const Vec2& origin, const Mat4& transformMatrix, const Color& backColor, const Rect& srcRect, const int zIndex = 0 );

  D3DXMATRIX convertToDirectXMatrix( const Mat4& mat ) const;

  RECT convertToWindowsRect( const Rect& rect ) const;

  void setProjectionMatrix( const Mat4& mat );

  void setWorldMatrix( const Mat4& mat );
  
  void setViewMatrix( const Mat4& mat );
};
}

#endif //!__ALADDIN_2D_GRAPHICS_2D_H__
