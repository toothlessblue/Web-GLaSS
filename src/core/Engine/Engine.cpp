#include "../RenderPipeline/RenderPipeline.hpp"
#include "../Screen/Screen.hpp"
#include "Engine.hpp"

Engine::Engine() {
    this->pipeline = new RenderPipeline();
    this->screen = new Screen(900, 450);
};

