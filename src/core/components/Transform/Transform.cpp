#include "Transform.hpp"
#include "../../../../include/glm/glm.hpp"
#include "../../../../include/glm/gtx/transform.hpp"
#include "../../../../include/glm/gtc/quaternion.hpp"
#include "../../../../include/glm/gtx/quaternion.hpp"

// TODO store matrices, recalculate them on get if their vec3 counterpart has changed

Transform::Transform() {
    this->scale = glm::vec3(1,1,1);
    this->position = glm::vec3(0,0,0);
    this->rotation = glm::quat(glm::vec3(0,0,0));
}

glm::mat4 Transform::getTranslationMatrix() {
    return glm::translate(glm::mat4(1.0f), this->position);
}

glm::mat4 Transform::getScaleMatrix() {
    return glm::scale(this->scale);
}

glm::mat4 Transform::getRotationMatrix() {
    return glm::toMat4(this->rotation);
}

glm::mat4 Transform::getModelMatrix() {
    glm::mat4 model = this->getTranslationMatrix() * this->getRotationMatrix() * this->getScaleMatrix();

    Transform* parent = this->parent;
    while (parent) {
        model *= (parent->getTranslationMatrix() * parent->getRotationMatrix() * parent->getScaleMatrix());
        parent = parent->parent;
    }

    return model;
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

glm::vec3 Transform::getWorldPosition() {
    glm::vec3 position = this->position;
    while (parent) {
        position += parent->position;
        parent = parent->parent;
    }
    return position;
}