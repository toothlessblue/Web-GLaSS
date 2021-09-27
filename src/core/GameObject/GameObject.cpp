#include "GameObject.hpp"
#include "../Component/Component.hpp"
#include "../components/Transform/Transform.hpp"

GameObject::GameObject() {
    this->transform = new Transform();
    this->addComponent(this->transform);
}

void GameObject::updateComponents() {
    for (Component *component : this->components) {
        component->update();
    }
}

void GameObject::addComponent(Component* component) {
    this->components.push_back(component);
    component->gameObject = this;
}