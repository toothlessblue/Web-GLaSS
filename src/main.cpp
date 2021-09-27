#include <stdio.h>
#include <stdlib.h>
#include "../include/glm/glm.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <emscripten.h>

#include "core/Screen/Screen.hpp"
#include "core/Shaders.hpp"
#include "core/components/Camera/Camera.hpp"
#include "core/RenderPipeline/RenderPipeline.hpp"
#include "core/components/TriangleRenderer/TriangleRenderer.hpp"
#include "core/GameObject/GameObject.hpp"

RenderPipeline* pipeline;

extern "C" void render() {
    pipeline->render();
}

extern "C" int main(int argc, char** argv) {
    Screen* screen = new Screen(900, 450);
    pipeline = new RenderPipeline();

    GLuint programID = CreateProgram("/lib/data/shaders/SimpleVertexShader.vert", "/lib/data/shaders/SimpleFragmentShader.frag");
    pipeline->setProgram(programID);

    emscripten_set_main_loop(render, 0, 0);
    
    Camera* camera = new Camera(90, screen->getRatio(), 0.1, 100);
    
    GameObject* gameObject = new GameObject();
    TriangleRenderer* triangleRenderer = gameObject->createComponent<TriangleRenderer>();
    pipeline->addRenderer(triangleRenderer); // TODO find a good way to do this automatically

    return 0;
}