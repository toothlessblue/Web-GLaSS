#include "GameEngine.hpp"

Screen GameEngine::screen = Screen(900, 450);
RenderPipeline GameEngine::renderPipeline = RenderPipeline();
WorldSpace GameEngine::worldSpace = WorldSpace();

void GameEngine::addGameObject(GameObject* newObject) {
    GameEngine::worldSpace.addGameObject(newObject);
}