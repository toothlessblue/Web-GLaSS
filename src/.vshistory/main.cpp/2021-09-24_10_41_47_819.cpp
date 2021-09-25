#include <stdio.h>
#include <stdlib.h>
#include "../include/glm/glm.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <emscripten.h>

#include "../src/core/Screen.hpp"
#include "../src/core/Shaders.hpp"
#include "../src/core/RenderPipeline.hpp"

using namespace glm;

RenderPipeline* pipeline;

extern "C" void render() {
    pipeline->render(;)
}

extern "C" int main(int argc, char** argv) {
    Screen screen(900, 450);
    pipeline = new RenderPipeline();

    GLuint programID = CreateProgram("/lib/data/shaders/SimpleVertexShader.vert", "/lib/data/shaders/SimpleFragmentShader.frag");
    pipeline->setProgram(programID);

    emscripten_set_main_loop(render, 0, 0);

    return 0;
}