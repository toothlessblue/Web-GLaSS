#include "GameObject.hpp"

GameObject::GameObject() {
    GameEngine::addGameObject(this);
    this->transform = new Transform();
    this->addComponent(this->transform);
}

GameObject::~GameObject() {
    for (Component *component : this->components) {
        delete component;
    }
    
    // Transform* GameObject::transform is in the component list, no need to call delete on it seperately
}

void GameObject::startComponents() {
    for (Component *component : this->components) {
        component->start();
    }
}

void GameObject::updateComponents() {
    for (Component *component : this->components) {
        if (component->isActive()) {
            component->update();
        }
    }
}

void GameObject::addComponent(Component* component) {
    component->gameObject = this;
    component->componentId = this->components.size();
    this->components.push_back(component);
}

void GameObject::setActive(bool value) {
    this->enabled = value;
}

bool GameObject::isActive() {
    if (Time::frameCount == this->frameCheckedActivity) {
        return this->cachedIsActive;
    }

    Transform* parent = this->transform->getParent();

    this->cachedIsActive = this->enabled && (!parent || parent->gameObject->isActive());
    this->frameCheckedActivity = Time::frameCount;

    return this->cachedIsActive;
}

/**
 * Irreversably switches the default Transform component for a RectTransform
 */
RectTransform* GameObject::useRectTransform() {
    // delete to free up memory, and replace with new transform - it should always be at index 0
    delete this->transform;
    RectTransform* rect = new RectTransform();
    this->transform = rect;
    this->components[0] = this->transform;
    rect->gameObject = this;
    return rect;
}

// TODO getRectTransform function

// Also has GameObject::createComponent, but this is defined in hpp instead