#include "WorldSpace.hpp"

void WorldSpace::addGameObject(GameObject* gameObject) {
    this->gameObjects.push_back(gameObject);
}

void WorldSpace::clearGameObjects() {
    for (GameObject *gameObject : this->gameObjects) {
        delete gameObject;
    }

    this->gameObjects.clear();
}

void WorldSpace::updateGameObjects() {
    for (GameObject *gameObject : this->gameObjects) {
        gameObject->updateComponents();
    }
}