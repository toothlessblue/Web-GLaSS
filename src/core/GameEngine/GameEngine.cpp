#include "GameEngine.hpp"
#include "../RenderPipeline/RenderPipeline.hpp"
#include "../Screen/Screen.hpp"
#include "../GameObject/GameObject.hpp"

RenderPipeline GameEngine::renderPipeline;
Screen GameEngine::screen;
WorldSpace GameEngine::screen;

void GameEngine::Initialise() {
    GameEngine::renderPipeline = RenderPipeline();
    GameEngine::screen = Screen(900, 450);
    GameEngine::worldSpace = WorldSpace();
}

GameObject* GameEngine::CreateGameObject() {
    GameObject* newObject = new GameObject();
    GameEngine::worldSpace.addGameObject(newObject);
    return newObject;
}