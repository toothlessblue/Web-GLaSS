#pragma once

#include "../RenderPipeline/RenderPipeline.hpp"
#include "../Screen/Screen.hpp"

class GameObject;

namespace GameEngine {
    extern RenderPipeline* renderPipeline;
    extern Screen* screen;

    void Initialise();
    GameObject* CreateGameObject();
};

#include "../GameObject/GameObject.hpp"