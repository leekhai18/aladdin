#ifndef __ALADDIN_UI_FONT_INFO_H__
#define __ALADDIN_UI_FONT_INFO_H__

#include "../core/ClassMeta.h"

enum {
  ALA_FONT_WEIGHT_THIN,
  ALA_FONT_WEIGHT_EXTRALIGHT,
  ALA_FONT_WEIGHT_LIGHT,
  ALA_FONT_WEIGHT_NORMAL,
  ALA_FONT_WEIGHT_MEDIUM,
  ALA_FONT_WEIGHT_SEMIBOLD,
  ALA_FONT_WEIGHT_BOLD,
  ALA_FONT_WEIGHT_EXTRABOLD,
  ALA_FONT_WEIGHT_HEAVY
};

NAMESPACE_ALA
{
ALA_CLASS_HEADER_0 ( FontInfo )
private:
  int _fontWeight;
  int _fontHeight;
  bool _italic;
public:
  FontInfo(const int fontWeight = ALA_FONT_WEIGHT_NORMAL, const int fontHeight = 14, const bool italic = false);
  FontInfo(const FontInfo &fontInfo);

  void setFontWeight(const int fontWeight);
  void setFontHeight(const int fontHeight);
  void setItalic(const bool italic);

  int getFontWeight() const;
  int getFontHeight() const;
  bool getItalic() const;

  bool operator==(const FontInfo& fontInfo) const;
  bool operator<(const FontInfo& fontInfo) const;

  virtual ~FontInfo();
};
}
#endif //!__ALADDIN_UI_FONT_INFO_H__
