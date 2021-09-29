#include <stdio.h>
#include <stdlib.h>
#include "../include/glm/glm.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <emscripten.h>

#include "core/GameEngine/GameEngine.hpp"
#include "core/Time/Time.hpp"
#include "core/Shaders/Shaders.hpp"
#include "core/components/Camera/Camera.hpp"
#include "core/components/TriangleRenderer/TriangleRenderer.hpp"
#include "core/GameObject/GameObject.hpp"

extern "C" void render() {
    Time::frameStart();
    
    GameEngine::renderPipeline->render();

    Time::frameEnd();
    Time::incrementFrameCounter();
}

extern "C" int main(int argc, char** argv) {
    GameEngine::Initialise();

    GLuint programID = Shaders::CreateProgram("/lib/data/shaders/SimpleVertexShader.vert", "/lib/data/shaders/SimpleFragmentShader.frag");
    GameEngine::renderPipeline->setProgram(programID);

    emscripten_set_main_loop(render, 0, 0);

    Camera* camera = new Camera(90, GameEngine::screen->getRatio(), 0.1, 100);
    
    GameObject* gameObject = GameEngine::CreateGameObject();
    TriangleRenderer* triangleRenderer = gameObject->createComponent<TriangleRenderer>();

    return 0;
}