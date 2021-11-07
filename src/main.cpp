#include <stdio.h>
#include <stdlib.h>
#include <string>

#include <emscripten.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/quaternion.hpp"
#include "../include/glm/gtx/quaternion.hpp"

// Game engine stuffs
#include "core/GameEngine/GameEngine.hpp"
#include "core/RuntimeFont/RuntimeFont.hpp"
#include "core/Input/Input.hpp"
#include "core/Time/Time.hpp"
#include "core/Shaders/Shaders.hpp"
#include "core/Lighting/Lighting.hpp"
#include "core/GameObject/GameObject.hpp"
#include "core/Material/Material.hpp"
#include "core/Texture/Texture.hpp"

// Components
#include "core/components/Camera/Camera.hpp"
#include "core/components/MeshRenderer/MeshRenderer.hpp"
#include "core/components/TextRenderer3d/TextRenderer3d.hpp"
#include "core/components/TextUI/TextUI.hpp"

#include "assets/CameraMouseController/CameraMouseController.hpp"
#include "assets/FloatingCameraKeyboardController/FloatingCameraKeyboardController.hpp"

TextUI* deltaTimeText;

extern "C" void gameLoop() {
    Time::frameStart();
    
    Input::Mouse::doLoop();
    GameEngine::renderPipeline.render();
    GameEngine::worldSpace.updateGameObjects();

    Time::frameEnd();
    Time::incrementFrameCounter();

    deltaTimeText->setText(&std::to_string(Time::deltaTime * 1000)[0]);
}

extern "C" int main(int argc, char** argv) {
    emscripten_set_main_loop(gameLoop, 0, 0);
    RuntimeFont::init();

    GameObject* text2d = GameEngine::CreateGameObject();
    RectTransform* rect = text2d->useRectTransform();
    deltaTimeText = text2d->createComponent<TextUI>();
    rect->height = deltaTimeText->getFont()->atlasHeight / 2.0f;
    rect->anchorMin = glm::vec2(0.0f, 0.0f);
    rect->anchorMax = glm::vec2(0.0f, 0.0f);

    GameObject* text2d2 = GameEngine::CreateGameObject();
    RectTransform* rect2 = text2d2->useRectTransform();
    TextUI* helloText = text2d2->createComponent<TextUI>();
    helloText->setText("Hello world!");
    rect2->height = rect->height;
    rect2->anchorMin = glm::vec2(0.0f, 1.0f);
    rect2->anchorMax = glm::vec2(0.0f, 1.0f);
    rect2->setParent(rect);

    GameObject* cube = GameEngine::CreateGameObject();
    GameObject* player = GameEngine::CreateGameObject();

    Camera* camera = player->createComponent<Camera>();
    camera->setAsActiveCamera();

    GameObject* light = GameEngine::CreateGameObject();
    light->createComponent<Lighting::PointLight>();
    light->transform->setPosition(glm::vec3(0, 2.0f, 0));

    player->createComponent<FloatingCameraKeyboardController>();
    player->createComponent<CameraMouseController>();
    player->transform->setPosition(glm::vec3(-3.0f,2.0f,3.0f));

    MeshRenderer* renderer = cube->createComponent<MeshRenderer>();
    Texture* texture = new Texture("/textures/NumberedCubeTex.DDS", DDS);
    renderer->material = new Material("/shaders/SimpleVertexShader.vert", "/shaders/SimpleFragmentShader.frag");
    renderer->material->setTexture("albedoTexture", texture);

    return 0;
}