#pragma once
#include "../WorldSpace/WorldSpace.hpp"
#include "../Screen/Screen.hpp"

class GameObject;
class RenderPipeline;

namespace GameEngine {
    extern WorldSpace worldSpace;
    extern RenderPipeline renderPipeline;
    extern Screen screen;

    GameObject* CreateGameObject();
};

#include "../GameObject/GameObject.hpp"
#include "../RenderPipeline/RenderPipeline.hpp"