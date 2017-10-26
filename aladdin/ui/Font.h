#ifndef __ALADDIN_UI_FONT_H__
#define __ALADDIN_UI_FONT_H__

#include "../core/GameResource.h"
#include "FontInfo.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1 ( Font, ala::GameResource )
private:
  std::map<FontInfo, ID3DXFont*> _fonts;
  bool _isSystemFont;
  std::string _fontName;
  std::string _fileName;
public:
  Font(const std::string& name, const std::string& fontName, const std::string& fontPath = "", Scene* scope = NULL);

  ID3DXFont* getDirectXFont(const FontInfo& fontInfo);

  virtual ~Font();

protected:
  void onLoad() override;

  void onRelease() override;
};
}
#endif //!__ALADDIN_UI_FONT_H__