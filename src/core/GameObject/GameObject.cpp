#include "GameObject.hpp"
#include "../Component/Component.hpp"
#include "../components/Transform/Transform.hpp"
#include "../Time/Time.hpp"

GameObject::GameObject() {
    this->transform = new Transform();
    this->addComponent(this->transform);
}

GameObject::~GameObject() {
    for (Component *component : this->components) {
        delete component;
    }

    this->transform = NULL;
}

void GameObject::updateComponents() {
    for (Component *component : this->components) {
        component->update();
    }

    this->transform->rotation *= glm::quat(glm::vec3(Time::getDeltaTime() * 0.25f, Time::getDeltaTime(), 0));
}

void GameObject::addComponent(Component* component) {
    this->components.push_back(component);
    component->gameObject = this;
}

// Also has GameObject::createComponent, but this is defined in hpp instead