#include "Camera.hpp"

Camera::Camera() {
    this->fieldOfView = GameEngine::screen.horizontalFieldOfViewDegreesToVerticalRadians(70.0f);                      
    this->ratio = GameEngine::screen.getRatio();
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
    GameEngine::renderPipeline.setActiveCamera(this);
}