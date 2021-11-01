#include "RectTransform.hpp"

RectTransform::RectTransform() {
    
}

void RectTransform::update() {

}

glm::vec2 RectTransform::calculatePosition() {
    glm::vec2 origin;
    if (this->parent) {
        origin = this->parent->position;
    }
}