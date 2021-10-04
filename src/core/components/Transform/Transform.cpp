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
        translation *= this->parent->getTranslationMatrix();
    }

    return translation;
}

glm::mat4 Transform::getScaleMatrix() {
    return glm::scale(this->scale);
}

// TODO. oh boy is this bit complex :D gotta learn quaternions and what not -- Lol nevermind GLM has a class for it, time to not learn this part ever
glm::mat4 Transform::getRotationMatrix() {
    return glm::toMat4(this->rotation);
}

glm::mat4 Transform::getModelMatrix() {
    return this->getTranslationMatrix() * this->getRotationMatrix() * this->getScaleMatrix();
}

// TODO maybe remove function, might be better placed somewhere else
glm::mat4 Transform::getModelViewProjectionMatrix(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {
    return projectionMatrix * viewMatrix * this->getModelMatrix();
}