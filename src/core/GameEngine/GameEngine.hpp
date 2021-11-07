#pragma once
#include "../Screen/Screen.hpp"

class GameObject;
class RenderPipeline;
class WorldSpace;

namespace GameEngine {
    extern WorldSpace worldSpace;
    extern RenderPipeline renderPipeline;
    extern Screen screen;

    void addGameObject(GameObject* gameObject);
};

#include "../GameObject/GameObject.hpp"
#include "../RenderPipeline/RenderPipeline.hpp"
#include "../WorldSpace/WorldSpace.hpp"