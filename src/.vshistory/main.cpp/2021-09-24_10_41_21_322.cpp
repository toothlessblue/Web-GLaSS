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

extern "C" void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(programID);

    // 1st attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        0,                    // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                    // size
        GL_FLOAT,             // type
        GL_FALSE,             // normalized?
        0,                    // stride
        (void*)0              // array buffer offset
    );
    // Draw the triangle!
    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDisableVertexAttribArray(0);
}

extern "C" int main(int argc, char** argv) {
    Screen screen(900, 450);
    RenderPipeline *pipeline = new RenderPipeline();

    GLuint programID = CreateProgram("/lib/data/shaders/SimpleVertexShader.vert", "/lib/data/shaders/SimpleFragmentShader.frag");
    pipeline->setProgram(programID);

    emscripten_set_main_loop(render, 0, 0);

    return 0;
}