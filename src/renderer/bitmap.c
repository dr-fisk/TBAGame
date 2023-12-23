#include <queue>

#include "bitmap.h"
#include "utility/plot_utility.h"

Bitmap::Bitmap(const int32_t cNumRows, const int32_t cNumCols, const lg::Color& crDefaultColor)
{
  mNumRows = cNumRows;
  mNumCols = cNumCols;
  mBitmap.resize(mNumRows * mNumCols, nullptr);
}

void Bitmap::constructBitmap(const std::vector<Vector2<int32_t>>& crPoints, const lg::Color& crColor)
{
  for(int32_t i = 0; i < mNumCols; i++)
  {
    for(int32_t j = 0; j < mNumRows; j ++)
    {
      mBitmap[i * mNumRows + j] = std::make_shared<Rect>(i, j, 1, 1, lg::Transparent);
    }
  }

  for(const auto& points : crPoints)
  {
    mBitmap.at(points.x * mNumRows + points.y)->setPos(points);
    mBitmap[points.x * mNumRows + points.y]->setColor(crColor);
  }
}

void Bitmap::fillColor(const int32_t cStartingPoint, const lg::Color& crColor)
{
  std::queue<int32_t> visited;
  int currPoint = -1;
  visited.push(cStartingPoint);
  mBitmap[cStartingPoint]->setColor(crColor);

  while(!visited.empty())
  {
    currPoint = visited.front();
    visited.pop();

    if(currPoint + mNumRows < mBitmap.size() && !(mBitmap[currPoint + mNumRows]->getRGBA() == crColor))
    {
      if(PlotUtility<int32_t>::arePointsTouching(mBitmap[currPoint + mNumRows]->getPos(), mBitmap[currPoint]->getPos()))
      {
        visited.push(currPoint + mNumRows);
        mBitmap[currPoint + mNumRows]->setColor(crColor);
      }
    }

    if(currPoint - mNumRows >= 0 && !(mBitmap[currPoint - mNumRows]->getRGBA() == crColor))
    {
      if(PlotUtility<int32_t>::arePointsTouching(mBitmap[currPoint - mNumRows]->getPos(), mBitmap[currPoint]->getPos()))
      {
        visited.push(currPoint - mNumRows);
        mBitmap[currPoint - mNumRows]->setColor(crColor);
      }
    }

    if(currPoint + 1 < mBitmap.size() && !(mBitmap[currPoint + 1]->getRGBA() == crColor))
    {
      if (PlotUtility<int32_t>::arePointsTouching(mBitmap[currPoint + 1]->getPos(), mBitmap[currPoint]->getPos()))
      {

        visited.push(currPoint + 1);
        mBitmap[currPoint + 1]->setColor(crColor);
      }
    }

    if(currPoint - 1 >= 0 && !(mBitmap[currPoint - 1]->getRGBA() == crColor))
    {
      if(PlotUtility<int32_t>::arePointsTouching(mBitmap[currPoint - 1]->getPos(), mBitmap[currPoint]->getPos()))
      {
        visited.push(currPoint - 1);
        mBitmap[currPoint - 1]->setColor(crColor);
      }
    }
  }
}

std::vector<std::shared_ptr<Rect>> Bitmap::getBitmap()
{
  return mBitmap;
}

Bitmap::~Bitmap()
{
}