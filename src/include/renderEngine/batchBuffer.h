#ifndef BATCHEDBUFFER_H
#define BATCHEDBUFFER_H

#include <vector>
#include <memory>
#include <string>
#include <bits/stdc++.h>

#include "utility/net_utility.h"
#include "glcommon.h"
#include "drawable/drawable.h"
#include "renderEngine/vertexArray.h"
#include "renderEngine/vertexBuffer.h"
#include "renderEngine/indexBuffer.h"
#include "renderEngine/shader.h"
#include "renderEngine/vertexBufferLayout.h"
#include "window/renderTarget.h"
#include "renderEngine/renderKey.h"

class Drawable;

const uint8_t TWO_D_COORDS = 2;
const uint8_t TRIANGLE_VERTICES2D = 3;
const uint8_t SQUARE_VERTICES2D = 4;
const uint8_t RGBA = 4;
const uint8_t SQUARE_INDICES = 6;
const uint8_t SQUARE_BYTE_SIZE = 32;
const uint32_t BYTES_IN_MB = 1048576;

class BatchBuffer
{
  public:
    BatchBuffer() = default;
    BatchBuffer(const uint32_t cNumVao, const uint32_t cNumVbo, const uint32_t cNumIbo, const uint32_t cNumShaders);
    std::shared_ptr<VertexBuffer> getVbo();
    std::shared_ptr<VertexArray> getVao();
    std::shared_ptr<IndexBuffer> getIbo();
    ~BatchBuffer() = default;
    void registerDrawable(Drawable *pDrawable, const uint32_t cTextureId, const uint32_t cLayer);
    void registerDrawable(Drawable *pDrawable, const RenderKey& crRenderKey);
    void unregisterDrawable(const RenderKey& crRenderKey);
    void initShader(const uint32_t cId, const std::string &crPath);
    void bindShader(const uint32_t cId);
    void bindVbo(const uint32_t cId);
    void bindIbo(const uint32_t cId);
    void bindVao(const uint32_t cId);
    void genIboBuffer(const uint32_t cId, const uint32_t cNumVertexes, const GLenum cDrawType);
    void genVboBuffer(const uint32_t cId, const uint32_t cNumVertexes, const GLenum cDrawType);
    void updateIboSubBuffer(const uint32_t cId, const uint32_t cIndex, const uint32_t cBuffSize, void *pBuffer);
    void updateVboSubBuffer(const uint32_t cId, const uint32_t cIndex, const uint32_t cBuffSize, void *pBuffer);
    void render(const uint32_t cVboId, const uint32_t cIboId, const std::shared_ptr<RenderTarget> &crpTarget);
    void setVaoAttributes(const uint32_t cId, const VertexBufferLayout& crLayout);
    uint32_t getIndicesCount(const uint32_t cId);
    int32_t getUniform(const uint32_t cId, const std::string& crUniform);
    int32_t getMaxTextureUnits();

  private:
    std::vector<std::shared_ptr<VertexBuffer>> mVbo;
    std::vector<std::shared_ptr<VertexArray>> mVao;
    std::vector<std::shared_ptr<IndexBuffer>> mIbo;
    std::vector<std::shared_ptr<Shader>> mShader;
    std::vector<Vertex> mVertexes;
    std::map<RenderKey, Drawable*> mQuads;
    std::map<int8_t, std::shared_ptr<TextureResource>> mTextureCache;
    int8_t mBoundedTextureIdx;
    uint64_t mRenderIdCount;
    bool mUpdateDraw;
    int32_t mMaxTextureUnits;

    void initBuffers();
};

#endif