#ifndef FONT_H
#define FONT_H

#define STB_TRUETYPE_IMPLEMENTATION
#define STBTT_STATIC
#include "glad/stb_truetype.h"
#include "common.h"

typedef stbtt_fontinfo lgFont;

class Font {
  public:
    Font();
    ~Font();
    int loadFromFile(std::string ttf);
  private:
    lgFont font;
};

#endif