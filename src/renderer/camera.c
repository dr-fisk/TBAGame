#include "renderer/camera.h"
#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"

OrthCamera::OrthCamera(const float cLeft, const float cRight, const float cBottom, const float cTop)
{
  mProjectionMatrix = glm::ortho(cLeft, cRight, cBottom, cTop, -1.0f, 1.0f);
  mViewMatrix = glm::mat4(1.0f);
  mViewProjectionMatrix = mProjectionMatrix * mViewMatrix;
  mPosition = glm::vec3(0.0f, 0.0f, 0.0f);
  mRotation = 0.0f;
}

void OrthCamera::setProjection(const float cLeft, const float cRight, const float cBottom, const float cTop)
{
  mProjectionMatrix = glm::ortho(cLeft, cRight, cBottom, cTop, -1.0f, 1.0f);
  updateViewMatrix();
}

void OrthCamera::updateViewMatrix()
{
  glm::mat4 transform = glm::translate(glm::mat4(1.0f), mPosition) *
                        glm::rotate(glm::mat4(1.0f), glm::radians(mRotation), glm::vec3(0, 0, 1));
  mViewMatrix = glm::inverse(transform);
  // Order matters for different Graphic Libraries
  mViewProjectionMatrix = mProjectionMatrix * mViewMatrix;
}