#ifndef TEXT_H
#define TEXT_H

#include <string>

#include "net_utility.h"
#include "font.h"
#include "drawable.h"

class Text : public Drawable
{
  public:
    Text(){}
    Text(const Font& crFont, const std::string& crText, const int32_t cHeight=8, const int32_t cWidth=8);
    std::vector<Vertex> getVertex();
    ~Text(){}
  private:
    Font mFont;
    std::string mText;
    std::vector<Vertex> mVertexes;
};

#endif