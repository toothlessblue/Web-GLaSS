#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <emscripten.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/quaternion.hpp"
#include "../include/glm/gtx/quaternion.hpp"

#include "core/GameEngine/GameEngine.hpp"
#include "core/RuntimeFont/RuntimeFont.hpp"
#include "core/Input/Input.hpp"
#include "core/Time/Time.hpp"
#include "core/Shaders/Shaders.hpp"
#include "core/Lighting/Lighting.hpp"
#include "core/components/Camera/Camera.hpp"
#include "core/components/MeshRenderer/MeshRenderer.hpp"
#include "core/GameObject/GameObject.hpp"
#include "core/Material/Material.hpp"
#include "core/Texture/Texture.hpp"

#include "assets/CameraMouseController/CameraMouseController.hpp"
#include "assets/FloatingCameraKeyboardController/FloatingCameraKeyboardController.hpp"

RuntimeFont::FontFace face;
GLuint fontProgram;

extern "C" void gameLoop() {
    Time::frameStart();
    
    Input::Mouse::doLoop();
    GameEngine::renderPipeline.render();
    GameEngine::worldSpace.updateGameObjects();    

    glUseProgram(fontProgram);
    face.renderText("Hello world!", 0, 0, 10, 10);

    Time::frameEnd();
    Time::incrementFrameCounter();
}

extern "C" int main(int argc, char** argv) {
    emscripten_set_main_loop(gameLoop, 0, 0);

    RuntimeFont::init();
    face = RuntimeFont::loadFont("/fonts/Roboto-Black.ttf");

    fontProgram = Shaders::CreateProgram("/shaders/BasicFont.vert", "/shaders/BasicFont.frag");

    GameObject* cube = GameEngine::CreateGameObject();
    GameObject* player = GameEngine::CreateGameObject();

    Camera* camera = player->createComponent<Camera>();
    camera->setAsActiveCamera();

    GameObject* light = GameEngine::CreateGameObject();
    light->createComponent<Lighting::PointLight>();
    light->transform->position = glm::vec3(0, 2.0f, 0);

    player->createComponent<FloatingCameraKeyboardController>();
    player->createComponent<CameraMouseController>();
    player->transform->position = glm::vec3(-3.0f,2.0f,3.0f);

    MeshRenderer* renderer = cube->createComponent<MeshRenderer>();
    Texture* texture = new Texture("/textures/NumberedCubeTex.DDS", DDS);
    renderer->material = new Material("/shaders/SimpleVertexShader.vert", "/shaders/SimpleFragmentShader.frag");
    renderer->material->setTexture("albedoTexture", texture);

    return 0;
}