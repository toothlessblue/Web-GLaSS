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
#include "Engine/GameEngine/GameEngine.hpp"
#include "Engine/RuntimeFont/RuntimeFont.hpp"
#include "Engine/Input/Input.hpp"
#include "Engine/Time/Time.hpp"
#include "Engine/Shaders/Shaders.hpp"
#include "Engine/Lighting/Lighting.hpp"
#include "Engine/GameObject/GameObject.hpp"
#include "Engine/Material/Material.hpp"
#include "Engine/Texture/Texture.hpp"
#include "Engine/ModelLoader/ModelLoader.hpp"

// Components
#include "Engine/components/Camera/Camera.hpp"
#include "Engine/components/MeshRenderer/MeshRenderer.hpp"
#include "Engine/components/TextRenderer3d/TextRenderer3d.hpp"
#include "Engine/components/TextUI/TextUI.hpp"

#include "assets/CameraMouseController/CameraMouseController.hpp"
#include "assets/FloatingCameraKeyboardController/FloatingCameraKeyboardController.hpp"
#include "assets/TransformRotator/TransformRotator.hpp"

TextUI* deltaTimeText;

extern "C" void gameLoop() {
    Time::frameStart();
    
    Input::Mouse::doLoop();
    GameEngine::renderPipeline.render();
    GameEngine::worldSpace.updateGameObjects();

    Time::frameEnd();
    Time::incrementFrameCounter();

    deltaTimeText->setText(&std::to_string(Time::frameTime * 1000)[0]);
}

extern "C" int main(int argc, char** argv) {
    emscripten_set_main_loop(gameLoop, 0, 0);
    RuntimeFont::init();
    GenericTextures::generate();

    GameObject* stage = new GameObject();
    MeshRenderer* stageMeshRenderer = stage->createComponent<MeshRenderer>();
    stageMeshRenderer->deleteMesh();
    stageMeshRenderer->setMesh(ModelLoader::OBJ::loadMesh("/models/stage.obj"));
    stageMeshRenderer->material = new Material("/shaders/SimpleVertexShader.vert", "/shaders/SimpleFragmentShader.frag");
    stageMeshRenderer->material->setTexture("albedoTexture", GenericTextures::whiteDot);
    stage->transform->setPosition(glm::vec3(0, -2.0f, 0));

    GameObject* text2d = new GameObject();
    RectTransform* rect = text2d->useRectTransform();
    deltaTimeText = text2d->createComponent<TextUI>();
    rect->height = deltaTimeText->getFont()->atlasHeight / 2.0f;
    rect->anchorMin = glm::vec2(0.0f, 0.0f);
    rect->anchorMax = glm::vec2(0.0f, 0.0f);

    GameObject* text2d2 = new GameObject();
    RectTransform* rect2 = text2d2->useRectTransform();
    TextUI* helloText = text2d2->createComponent<TextUI>();
    helloText->setText("Hello world!");
    rect2->height = rect->height;
    rect2->anchorMin = glm::vec2(0.0f, 1.0f);
    rect2->anchorMax = glm::vec2(0.0f, 1.0f);
    rect2->setParent(rect);

    GameObject* light = new GameObject();
    light->createComponent<Lighting::PointLight>();
    light->transform->setPosition(glm::vec3(0.0f, 2.0f, 4.0f));

    GameObject* player = new GameObject();
    Camera* camera = player->createComponent<Camera>();
    camera->setAsActiveCamera();
    player->createComponent<FloatingCameraKeyboardController>();
    player->createComponent<CameraMouseController>();
    player->transform->setPosition(glm::vec3(-3.0f,2.0f,3.0f));

    GameObject* cube = new GameObject();
    cube->createComponent<TransformRotator>();
    MeshRenderer* renderer = cube->createComponent<MeshRenderer>();
    Texture* texture = new Texture("/textures/NumberedCubeTex.DDS", DDS);
    renderer->material = new Material("/shaders/SimpleVertexShader.vert", "/shaders/SimpleFragmentShader.frag");
    renderer->material->setTexture("albedoTexture", texture);

    GameEngine::worldSpace.startGameObjects();

    return 0;
}