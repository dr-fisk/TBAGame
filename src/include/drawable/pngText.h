#ifndef PNGTEXT_H
#define PNGTEXT_H

#include <vector>
#include <string>

#include "glcommon.h"
#include "drawable/drawable.h"
#include "drawable/rectangle.h"
#include "pngFont.h"
#include "resource/textureResource.h"

class PngText : public Drawable
{
  public:
    PngText(){}
    PngText(const std::string &crText, PngFont &rFont);
    ~PngText();
    std::shared_ptr<TextureResource> getResource() {return nullptr;}
    std::vector<Vertex> getVertex();
    void getVertex(std::vector<Vertex>& rBatchVertexes, uint32_t& rVertexIdx){}
  private:
    std::vector<Vertex> mVertex;
    TextureResource mTexture;

    void updateTextPos(Rect &rCurrLetter, const uint32_t cMeshIndex, const uint32_t cTotalIndex);
};

#endif