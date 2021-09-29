#include "GameEngine.hpp"
#include "../RenderPipeline/RenderPipeline.hpp"
#include "../Screen/Screen.hpp"
#include "../GameObject/GameObject.hpp"

RenderPipeline GameEngine::renderPipeline = RenderPipeline();
Screen GameEngine::screen = Screen(900, 450);
WorldSpace GameEngine::worldSpace = WorldSpace();

GameObject* GameEngine::CreateGameObject() {
    GameObject* newObject = new GameObject();
    GameEngine::worldSpace.addGameObject(newObject);
    return newObject;
}