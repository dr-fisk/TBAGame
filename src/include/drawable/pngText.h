#ifndef PNGTEXT_H
#define PNGTEXT_H

#include <vector>
#include <string>

#include "glcommon.h"
#include "drawable/drawable.h"
#include "drawable/rectangle.h"
#include "pngFont.h"

class PngText : public Drawable {
  public:
    PngText(){}
    PngText(const std::string &crText, PngFont &rFont);
    virtual ~PngText();
    virtual std::vector<RenderData> getRenderData();
  private:
    std::vector<RenderData> mRenderData;

    void updateTextPos(Rect &rCurrLetter, const uint32_t cMeshIndex, const uint32_t cTotalIndex);
};

#endif