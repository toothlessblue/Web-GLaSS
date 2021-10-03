#include <stdio.h>
#include <stdlib.h>
#include "../include/glm/glm.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <emscripten.h>

#include "core/GameEngine/GameEngine.hpp"
#include "core/Input/Input.hpp"
#include "core/Time/Time.hpp"
#include "core/Shaders/Shaders.hpp"
#include "core/components/Camera/Camera.hpp"
#include "core/components/TriangleRenderer/TriangleRenderer.hpp"
#include "core/GameObject/GameObject.hpp"
#include "core/Material/Material.hpp"
#include "core/Texture/Texture.hpp"

extern "C" void gameLoop() {
    Time::frameStart();
    
    Input::Mouse::doLoop();
    GameEngine::renderPipeline.render();
    GameEngine::worldSpace.updateGameObjects();    

    Time::frameEnd();
    Time::incrementFrameCounter();
}

extern "C" int main(int argc, char** argv) {
    emscripten_set_main_loop(gameLoop, 0, 0);

    Camera* camera = new Camera(90, GameEngine::screen.getRatio(), 0.1, 100);

    GameObject* gameObject = GameEngine::CreateGameObject();
    TriangleRenderer* renderer = gameObject->createComponent<TriangleRenderer>();
    renderer->material = new Material("/shaders/SimpleTextureShader.vert", "/shaders/SimpleTextureShader.frag");

    Texture* texture = new Texture("/textures/NumberedCubeTex.DDS", DDS);
    renderer->material->setTexture("myTextureSampler", texture);

    delete camera;

    return 0;
}