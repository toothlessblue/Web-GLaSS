#include "Transform.hpp"
#include "../../../../include/glm/glm.hpp"
#include "../../../../include/glm/gtx/transform.hpp"

Transform::Transform() { }

glm::mat4 Transform::getTranslationMatrix() {
    return glm::translate(glm::mat4(), this->position);
}

glm::mat4 Transform::getScaleMatrix() {
    return glm::scale(this->scale);
}

glm::mat4 Transform::getRotationMatrix() {
    return glm::mat4(); // TODO oh boy is this bit complex :D gotta learn quaternions and what not
}

glm::mat4 Transform::getModelMatrix() {
    return this->getTranslationMatrix() * this->getRotationMatrix() * this->getScaleMatrix();
}

glm::mat4 Transform::getModelViewProjectionMatrix(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {
    return projectionMatrix * viewMatrix * this->getModelMatrix();
}