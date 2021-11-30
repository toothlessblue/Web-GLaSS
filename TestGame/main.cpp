#include <iostream>
#include "../src/WebGLaSS/GameObject/GameObject.hpp"
#include "../src/WebGLaSS/Math/Math.hpp"
#include "../src/WebGLaSS/components/MeshRenderer/MeshRenderer.hpp"
#include "../src/WebGLaSS/components/TextUI/TextUI.hpp"
#include "../src/WebGLaSS/components/Camera/Camera.hpp"

#include "assets/CameraMouseController/CameraMouseController.hpp"
#include "assets/FloatingCameraKeyboardController/FloatingCameraKeyboardController.hpp"
#include "assets/TransformRotator/TransformRotator.hpp"

TextUI* deltaTimeText;
Math::RollingAverage deltaTimeAverage(300);

extern "C" void Start() {
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
    light->transform->setPosition(glm::vec3(0.0f, 1.5f, 4.0f));

    GameObject* light2 = new GameObject();
    light2->createComponent<Lighting::PointLight>();
    light2->transform->setPosition(glm::vec3(3.0f, 2.0f, -0.75f));

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
}

extern "C" void Update() {
    deltaTimeAverage.addValue(Time::frameTime);
    deltaTimeText->setText(&std::to_string(deltaTimeAverage.getAverage() * 1000).append("ms")[0]);
}