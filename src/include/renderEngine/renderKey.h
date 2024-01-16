#ifndef RENDER_KEY_H
#define RENDER_KEY_H

#include <cstdint>
#include <iostream>

class RenderKey
{
  public:
    RenderKey() = default;
    RenderKey(const uint64_t cId, const uint32_t cTextureId, const uint32_t cLayer)
    {
      mId = cId;
      mTextureId = cTextureId;
      mLayer = cLayer;
    }

    ~RenderKey() = default;
    bool operator<(const RenderKey& rhs) const
    {
      return (mLayer < rhs.mLayer) ||(mLayer == rhs.mLayer && mId < rhs.mId);
    }

    uint64_t getId() const
    {
      return mId;
    }

    uint32_t getLayer() const
    {
      return mLayer;
    }
  private:
    uint64_t mId;
    uint32_t mTextureId;
    uint32_t mLayer;
};

#endif