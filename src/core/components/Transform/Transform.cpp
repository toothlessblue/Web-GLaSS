#include "Transform.hpp"
#include "../../../../include/glm/glm.hpp"
#include "../../../../include/glm/gtx/transform.hpp"

Transform::Transform() {
    this->scale = glm::vec3(1,1,1);
    this->position = glm::vec3(0,0,0);
    this->rotation = glm::vec3(0,0,0);
}

glm::mat4 Transform::getTranslationMatrix() {
    return glm::translate(glm::mat4(1.0f), this->position);
}

glm::mat4 Transform::getScaleMatrix() {
    return glm::scale(this->scale);
}

// TODO oh boy is this bit complex :D gotta learn quaternions and what not
glm::mat4 Transform::getRotationMatrix() {
    return glm::mat4(1.0f); // For now just returning identity
}

glm::mat4 Transform::getModelMatrix() {
    return this->getTranslationMatrix() * this->getRotationMatrix() * this->getScaleMatrix();
}

// TODO maybe remove function, might be better placed somewhere else
glm::mat4 Transform::getModelViewProjectionMatrix(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {
    return projectionMatrix * viewMatrix * this->getModelMatrix();
}