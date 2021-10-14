#include "Transform.hpp"
#include "../../../../include/glm/glm.hpp"
#include "../../../../include/glm/gtx/transform.hpp"
#include "../../../../include/glm/gtc/quaternion.hpp"
#include "../../../../include/glm/gtx/quaternion.hpp"

Transform::Transform() {
    this->scale = glm::vec3(1,1,1);
    this->position = glm::vec3(0,0,0);
    this->rotation = glm::quat(glm::vec3(0,0,0));
}

glm::mat4 Transform::getTranslationMatrix() {
    glm::mat4 translation = glm::translate(glm::mat4(1.0f), this->position);
    
    if (this->parent) {
        // TODO recursive call is computationally inefficient, replace with while loop
        // translation *= this->parent->getTranslationMatrix(); This appears to be calling infinitely?
    }

    return translation;
}

glm::mat4 Transform::getScaleMatrix() {
    return glm::scale(this->scale);
}

glm::mat4 Transform::getRotationMatrix() {
    return glm::toMat4(this->rotation);
}

glm::mat4 Transform::getModelMatrix() {
    return this->getTranslationMatrix() * this->getRotationMatrix() * this->getScaleMatrix();
}

glm::vec3 Transform::getForwards() {
    return glm::rotate(glm::inverse(this->rotation), glm::vec3(0, 0, 1));
}

glm::vec3 Transform::getLeft() {
    return glm::rotate(glm::inverse(this->rotation), glm::vec3(1, 0, 0));
}

glm::vec3 Transform::getUp() {
    return glm::rotate(glm::inverse(this->rotation), glm::vec3(0, 1, 0));
}