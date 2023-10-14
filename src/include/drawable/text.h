#ifndef TEXT_H
#define TEXT_H

#include "common.h"
#include "font.h"

class Text
{
  public:
    Text(){}
    Text(const Font cFont, const std::string cText, const int32_t cHeight=8, const int32_t cWidth=8);
    ~Text(){}
  private:
    Font mFont;
    std::string mLabel;
    std::vector<Bitmap> mRasterizer;
};

#endif