#pragma once
#include "RenderPipeline/RenderPipeline.hpp"
#include "WorldSpace/WorldSpace.hpp"
#include "Screen/Screen.hpp"

class GameObject;
class Screen;
class RenderPipeline;
class WorldSpace;

namespace WebGLaSS {
    extern WorldSpace worldSpace;
    extern RenderPipeline renderPipeline;
    extern Screen screen;

    void addGameObject(GameObject* gameObject);
};
