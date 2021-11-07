#include "RectTransform.hpp"

RectTransform::RectTransform() {
    
}

void RectTransform::update() {

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
        return this->parent->getPosition();
    }
}

glm::vec3 RectTransform::getPosition() {
    glm::vec3 parentPosition = this->getParentPosition();
    glm::vec2 parentDimensions = this->getParentDimensions();


    float xStart = parentPosition.x;
    float xEnd = xStart + parentDimensions.x;
    float yStart = parentPosition.y;
    float yEnd = yStart + parentDimensions.y;

    float anchoredX = Math::lerp(xStart, xEnd, this->anchorMin.x);
    float anchoredY = Math::lerp(yStart, yEnd, this->anchorMin.y);

    float left = anchoredX + this->position.x;
    float top = anchoredY + this->position.y;

    return glm::vec3(left, top, 0);
}

glm::vec3 RectTransform::getMaxPosition() {
    glm::vec3 parentPosition = this->getParentPosition();
    glm::vec2 parentDimensions = this->getParentDimensions();

    float xStart = parentPosition.x;
    float xEnd = xStart + parentDimensions.x;
    float yStart = parentPosition.y;
    float yEnd = yStart + parentDimensions.y;

    float anchoredX = Math::lerp(xStart, xEnd, this->anchorMax.x);
    float anchoredY = Math::lerp(yStart, yEnd, this->anchorMax.y);

    float right = anchoredX - this->position.x - this->width;
    float bottom = anchoredY - this->position.y - this->height;

    return glm::vec3(right, bottom, 0);
}

glm::vec2 RectTransform::getDimensions() {
    return glm::vec2(this->width, this->height);
}

glm::mat4 RectTransform::getTranslationMatrix() {
    glm::vec3 position = this->getPosition();

    position.y += this->height;

    // Divide by resolution to get 0 -> 1 space
    position.x /= GameEngine::screen.width;
    position.y /= GameEngine::screen.height;

    // Invert Y so 0 is top rather than bottom
    position.y = 1 - position.y;

    // Multiply by 2: 0 -> 2 space
    position *= 2;

    // -1 offset: -1 -> 1 space, which is what OpenGL needs
    position.x -= 1;
    position.y -= 1;

    return glm::translate(glm::mat4(1.0f), position);
}

glm::mat4 RectTransform::getModelMatrix() {
    glm::mat4 model = this->getTranslationMatrix() * this->getRotationMatrix() * this->getScaleMatrix();

    Transform* parent = this->getParent();
    while (parent) {
        model *= (parent->getRotationMatrix() * parent->getScaleMatrix());
        parent = parent->getParent();
    }

    return model;
}

void RectTransform::setLeft(float v) {
    float delta = v - this->getPosition().x;

    this->position.x += delta;
    this->width += delta;
}
void RectTransform::setRight(float v) {
    float delta = v - this->getMaxPosition().x;

    this->width += delta;
}
void RectTransform::setTop(float v) {
    float delta = v - this->getPosition().y;

    this->position.y += delta;
    this->height += delta;
}
void RectTransform::setBottom(float v) {
    float delta = v - this->getMaxPosition().y;

    this->height += delta;
}