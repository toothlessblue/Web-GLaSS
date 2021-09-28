#include "GameEngine.hpp"
#include "../RenderPipeline/RenderPipeline.hpp"
#include "../Screen/Screen.hpp"
#include "../GameObject/GameObject.hpp"

RenderPipeline* GameEngine::renderPipeline;
Screen* GameEngine::screen;

void GameEngine::Initialise() {
    GameEngine::renderPipeline = new RenderPipeline();
    GameEngine::screen = new Screen(900, 450);
}

GameObject* GameEngine::CreateGameObject() {
    GameObject* newObject = new GameObject();

    return newObject;
}