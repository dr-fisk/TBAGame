#ifndef BITMAP_H
#define BITMAP_H

#include <memory>

#include "drawable/rectangle.h"
#include "color.h"
#include "Vector.h"

class Bitmap
{
  public:
    Bitmap() : mNumRows{0}, mNumCols{0} {}
    Bitmap(const int32_t cNumRows, const int32_t cNumCols, const lg::Color& crDefaultColor=lg::Black);
    ~Bitmap();
    void constructBitmap(const std::vector<Vector2<float>>& crPoints, const lg::Color& crColor);
    void fillColor(const int32_t cStartingPoint, const lg::Color& crColor);
    std::vector<std::shared_ptr<Rect>> getBitmap();
  private:
    std::vector<std::shared_ptr<Rect>> mBitmap;
    int32_t mNumRows;
    int32_t mNumCols;
};

#endif