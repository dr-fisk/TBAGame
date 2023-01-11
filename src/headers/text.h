#ifndef TEXT_H
#define TEXT_H

#include "Drawable.h"
#include "font.h"

class Text : public Drawable {
  public:
    Text(){}
    Text(const std::string &crText, Font &rFont);
    virtual ~Text();
    virtual std::vector<RenderData> getRenderData();
  private:
    std::vector<RenderData> mRenderData;

    void updateTextPos(Rect &rCurrLetter, const uint32_t cMeshIndex, const uint32_t cTotalIndex);
};

#endif