#include "RenderPipeline.hpp"

RenderPipeline::RenderPipeline() {
    
}

void RenderPipeline::setProgram(GLuint programID) {
    this->programID = programID;
}

void RenderPipeline::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(this->programID); // TODO place this in render function of each renderer to allow seperate shaders for different renderers

    for (Renderer *renderer : this->renderers) {
        renderer->preRenderCheck();
        renderer->render();
    }
}

unsigned int RenderPipeline::addRenderer(Renderer* renderer) {
    this->renderers.push_back(renderer);

    unsigned int index = this->renderers.size() - 1;
    renderer->setId(index);
    return index;
}