#include "Component.hpp"

Component::Component() { }
void Component::update() { }

bool Component::isActive() {
    return this->enabled;
}

void Component::setActive(bool value) {
    this->enabled = value;
}