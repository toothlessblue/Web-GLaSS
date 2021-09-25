#include "../Component/Component.hpp"
#include "GameObject.hpp"

GameObject::GameObject() { }
void GameObject::updateComponents() {
    for (Component *component : this->components) {
        component->update();
    }
}

void GameObject::addComponent(Component* component) {
    this->components.push_back(component);
}