#ifndef TEXT_H
#define TEXT_H

#include "Drawable.h"
#include "font.h"

class Text : public Drawable {
  public:
    Text(){}
    Text(std::string text, Font &font);
    virtual ~Text();
    virtual std::vector<RenderData> getRenderData();
  private:
    std::vector<RenderData> renderData;

    void updateTextPos(Rect &currLetter, uint32_t meshIndex, uint32_t totalIndex);
};

#endif