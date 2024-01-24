#ifndef CAMERA_H
#define CAMERA_H

#define GLM_FORCE_CTOR_INIT
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"

class OrthCamera
{
  public:
    OrthCamera() = default;
    OrthCamera(const float cLeft, const float cRight, const float cBottom, const float cTop);
    ~OrthCamera() = default;

    void setPosition(const glm::vec3& crPosition) { mPosition = crPosition; updateViewMatrix(); }
    void setRotation(const float cRotation) { mRotation = cRotation; updateViewMatrix(); }
    void setProjection(const float cLeft, const float cRight, const float cBottom, const float cTop);
    const glm::vec3& getPosition() const { return mPosition; }
    float getRotation() const { return mRotation; }
    const glm::mat4& getProjectionMatrix() const { return mProjectionMatrix; }
    const glm::mat4& getViewMatrix() const { return mViewMatrix; }
    const glm::mat4& getViewProjectionMatrix() const { return mViewProjectionMatrix; }
    void unsetUpdateFlag() {  mUpdateGeometry = false; }
    bool geometryNeedUpdate() const { return mUpdateGeometry; }
  private:
    void updateViewMatrix();
  
    glm::mat4 mProjectionMatrix;
    glm::mat4 mViewMatrix;
    glm::mat4 mViewProjectionMatrix;

    glm::vec3 mPosition;
    float mRotation;
    bool mUpdateGeometry;
};

#endif