#pragma once

#include <list>
#include "../GameObject/GameObject.hpp"

class WorldSpace {
public:
    void addGameObject(GameObject*);
    void clearGameObjects();
    void updateGameObjects();

private:
    std::list<GameObject*> gameObjects;

};