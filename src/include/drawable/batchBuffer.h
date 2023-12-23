#ifndef BATCHEDBUFFER_H
#define BATCHEDBUFFER_H

#include <vector>
#include <memory>
#include <string>
#include <bits/stdc++.h>

#include "utility/net_utility.h"
#include "glcommon.h"
#include "drawable/drawable.h"
#include "drawable/vertexArray.h"
#include "drawable/vertexBuffer.h"
#include "drawable/indexBuffer.h"
#include "drawable/shader.h"
#include "vertexBufferLayout.h"
#include "drawable/texture.h"

const uint8_t TWO_D_COORDS = 2;
const uint8_t TRIANGLE_VERTICES2D = 3;
const uint8_t SQUARE_VERTICES2D = 4;
const uint8_t RGBA = 4;
const uint8_t SQUARE_INDICES = 6;
const uint8_t SQUARE_BYTE_SIZE = 32;
const uint32_t BYTES_IN_MB = 1048576;

class BatchBuffer {
  public:
    BatchBuffer() = default;
    BatchBuffer(const uint32_t cNumVao, const uint32_t cNumVbo, const uint32_t cNumIbo, const uint32_t cNumShaders,
                const uint32_t cNumTextures);
    std::shared_ptr<VertexBuffer> getVbo();
    std::shared_ptr<VertexArray> getVao();
    std::shared_ptr<IndexBuffer> getIbo();
    ~BatchBuffer() = default;
    static void concatVertex(const std::vector<Drawable*> &crBufferData, std::vector<Vertex> &rData);
    void registerDrawable(const uint32_t cVboId, const uint32_t cIboId, std::shared_ptr<Drawable> pBufferData);
    void initShader(const uint32_t cId, const std::string &crPath);
    void initTexture(const uint32_t cId, const std::string &crPath);
    void initTexture(const uint32_t cId, void *pBuff, const uint32_t cHeight, const uint32_t cWidth,
                     const uint32_t cBpp);
    void bindShader(const uint32_t cId);
    void bindVbo(const uint32_t cId);
    void bindIbo(const uint32_t cId);
    void bindVao(const uint32_t cId);
    void bindTexture(const uint32_t cId, const uint32_t cSlot);
    void genIboBuffer(const uint32_t cId, const uint32_t cNumVertexes, const GLenum cDrawType);
    void genVboBuffer(const uint32_t cId, const uint32_t cNumVertexes, const GLenum cDrawType);
    void updateIboSubBuffer(const uint32_t cId, const uint32_t cIndex, const uint32_t cBuffSize, void *pBuffer);
    void updateVboSubBuffer(const uint32_t cId, const uint32_t cIndex, const uint32_t cBuffSize, void *pBuffer);
    void update(const uint32_t cVboId, const uint32_t cIboId);
    void setVaoAttributes(const uint32_t cId, const VertexBufferLayout &crLayout);
    uint32_t getIndicesCount(const uint32_t cId);
    int32_t getUniform(const uint32_t cId, const std::string &crUniform);

  private:
    std::vector<std::shared_ptr<VertexBuffer>> mVbo;
    std::vector<std::shared_ptr<VertexArray>> mVao;
    std::vector<std::shared_ptr<IndexBuffer>> mIbo;
    std::vector<std::shared_ptr<Shader>> mShader;
    std::vector<std::shared_ptr<Texture>> mTexture;
    std::vector<uint8_t> mBuffer;
    std::unordered_map<int32_t, std::shared_ptr<Drawable>> mQuads;
    uint64_t mRegisteredDrawables;
    uint64_t mNextAvailableAddress;
    uint64_t mNumVertices;
    uint32_t mRenderIdCount;
    bool mUpdateDraw;

    std::vector<uint32_t> createRectIndices(const uint32_t cVboSize);
    std::vector<uint32_t> createTriIndices(const uint32_t cVboSize);
    void initBuffers();
};

#endif