#include "GameEngine.hpp"

Screen GameEngine::screen = Screen(900, 450); // TODO this resolution is set as magic value in shaders, get it from uniforms before changing this
RenderPipeline GameEngine::renderPipeline = RenderPipeline();
WorldSpace GameEngine::worldSpace = WorldSpace();

GameObject* GameEngine::CreateGameObject() {
    GameObject* newObject = new GameObject();
    GameEngine::worldSpace.addGameObject(newObject);
    return newObject;
}