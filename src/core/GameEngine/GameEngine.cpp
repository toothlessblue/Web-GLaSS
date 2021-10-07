#include "GameEngine.hpp"

Screen GameEngine::screen = Screen(900, 450);
RenderPipeline GameEngine::renderPipeline = RenderPipeline();
WorldSpace GameEngine::worldSpace = WorldSpace();

GameObject* GameEngine::CreateGameObject() {
    GameObject* newObject = new GameObject();
    GameEngine::worldSpace.addGameObject(newObject);
    return newObject;
}