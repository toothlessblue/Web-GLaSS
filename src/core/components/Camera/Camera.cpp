#include "../../Component/Component.hpp"
#include "../../../../include/glm/glm.hpp"
#include "../../../../include/glm/gtx/transform.hpp"
#include "../../../../include/glm/gtc/matrix_transform.hpp"
#include "Camera.hpp"

Camera::Camera(float fieldOfView, float ratio, float nearClipPlane, float farClipPlane) {
    this->fieldOfView = fieldOfView;
    this->ratio = ratio;
    this->nearClipPlane = nearClipPlane;
    this->farClipPlane = farClipPlane;
}

glm::mat4 Camera::getCameraMatrix() {
    return glm::perspective(this->fieldOfView, this->ratio, this->nearClipPlane, this->farClipPlane);
}

glm::mat4 Camera::getProjectionMatrix() {
    return glm::lookAt(
        this->gameObject->transform->position,
        glm::vec3(),
        glm::vec3(0, 1, 0)
    );
}