#include "GameObject.hpp"

GameObject::GameObject() {
    this->transform = new Transform();
    this->addComponent(this->transform);
}

GameObject::~GameObject() {
    for (Component *component : this->components) {
        delete component;
    }
    
    // Transform* GameObject::transform is in the component list, no need to call delete on it seperately
}

void GameObject::updateComponents() {
    for (Component *component : this->components) {
        if (component->enabled) {
            component->update();
        }
    }
}

void GameObject::addComponent(Component* component) {
    component->gameObject = this;
    component->componentId = this->components.size();
    this->components.push_back(component);
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
    return rect;
}

// TODO getRectTransform function

// Also has GameObject::createComponent, but this is defined in hpp instead