#include "Camera.hpp"

Camera::Camera() {
    this->fieldOfView = WebGLaSS::screen.horizontalFieldOfViewDegreesToVerticalRadians(70.0f);                      
    this->ratio = WebGLaSS::screen.getRatio();
    this->nearClipPlane = 0.1f;
    this->farClipPlane = 100.0f;
}

glm::mat4 Camera::getProjectionMatrix() {
    return glm::perspective(this->fieldOfView, this->ratio, this->nearClipPlane, this->farClipPlane);
}

glm::mat4 Camera::getViewMatrix() {
    return glm::toMat4(this->gameObject->transform->getRotation()) * glm::translate(glm::mat4(1.0f), -this->gameObject->transform->getPosition());
}

void Camera::setAsActiveCamera() {
    WebGLaSS::renderPipeline.setActiveCamera(this);
}