#ifndef TEXT_H
#define TEXT_H

#include <string>

#include "utility/net_utility.h"
#include "font.h"
#include "drawable.h"

class Text : public Drawable
{
  public:
    Text(){}
    Text(const Font& crFont, const std::string& crText, const int32_t cTop, const int32_t cLeft,
         const int32_t cLineWrap=-1);
    std::vector<Vertex> getVertex();
    void gridfitText();
    ~Text(){}
  private:
    Font mFont;
    std::string mText;
    std::vector<Vertex> mVertexes;

    int32_t mTop;
    int32_t mLeft;
    int32_t mLineWrap;
};

#endif