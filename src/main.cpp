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

#include "core/components/CameraMouseController/CameraMouseController.hpp"

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

    GameObject* cube = GameEngine::CreateGameObject();
    GameObject* player = GameEngine::CreateGameObject();
    Camera* camera = player->createComponent<Camera>();
    camera->setAsActiveCamera();

    player->createComponent<CameraMouseController>();

    player->transform->position = glm::vec3(3.0f,0.0f,-3.0f);

    TriangleRenderer* renderer = cube->createComponent<TriangleRenderer>();

    renderer->material = new Material("/shaders/SimpleTextureShader.vert", "/shaders/SimpleTextureShader.frag");

    Texture* texture = new Texture("/textures/NumberedCubeTex.DDS", DDS);
    renderer->material->setTexture("myTextureSampler", texture);

    return 0;
}