#include "TransformRotator.hpp"

TransformRotator::TransformRotator() {

}

void TransformRotator::update() {
    this->gameObject->transform->addRotation(glm::vec3(0, Time::deltaTime, 0));
}
