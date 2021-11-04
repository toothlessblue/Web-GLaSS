#include "RectTransform.hpp"

RectTransform::RectTransform() {
    
}

void RectTransform::update() {

}

void RectTransform::updateChildPositions() {
    
}

glm::vec2 RectTransform::getParentDimensions() {
    if (!this->parent) {
        return glm::vec2(GameEngine::screen.width, GameEngine::screen.height);
    } else {
        return this->parent->getDimensions();
    }
}

glm::vec3 RectTransform::getParentPosition() {
    if (!this->parent) {
        return glm::vec3(0, 0, 0);
    } else {
        return this->parent->position;
    }
}

glm::vec2 RectTransform::calculatePosition() {
    glm::vec2 origin;
    if (this->parent) {
        origin = this->parent->position;
    }
}

glm::vec2 RectTransform::getDimensions() {
    return glm::vec2(this->width, this->height);
}

float RectTransform::getLeft() {
    glm::vec3 parentPosition = this->getParentPosition();
    glm::vec2 parentDimensions = this->getParentDimensions();

    float xStart = parentPosition.x;
    float xEnd = xStart + parentDimensions.x;

    float anchoredX = Math::lerp(xStart, xEnd, this->anchorMin.x);

    return this->position.x - anchoredX;
}

void RectTransform::setLeft(float v) {
    float delta = v - this->getLeft();

    this->position.x += delta;
    this->width += delta;
}

float RectTransform::getRight() {
    glm::vec3 parentPosition = this->getParentPosition();
    glm::vec2 parentDimensions = this->getParentDimensions();

    float xStart = parentPosition.x;
    float xEnd = xStart + parentDimensions.x;

    float anchoredX = Math::lerp(xStart, xEnd, this->anchorMax.x);

    return anchoredX - this->position.x + this->width;
}

void RectTransform::setRight(float v) {
    float delta = v - this->getRight();

    this->width += delta;
}

float RectTransform::getTop() {
    glm::vec3 parentPosition = this->getParentPosition();
    glm::vec2 parentDimensions = this->getParentDimensions();

    float yStart = parentPosition.y;
    float yEnd = yStart + parentDimensions.y;

    float anchoredY = Math::lerp(yStart, yEnd, this->anchorMin.y);

    return this->position.y - anchoredY;
}

void RectTransform::setTop(float v) {
    float delta = v - this->getTop();

    this->position.y += delta;
    this->height += delta;
}

float RectTransform::getBottom() {
    glm::vec3 parentPosition = this->getParentPosition();
    glm::vec2 parentDimensions = this->getParentDimensions();

    float yStart = parentPosition.y;
    float yEnd = yStart + parentDimensions.y;

    float anchoredY = Math::lerp(yStart, yEnd, this->anchorMax.y);

    return anchoredY - this->position.y + this->height;
}

void RectTransform::setBottom(float v) {
    float delta = v - this->getBottom();

    this->height += delta;
}