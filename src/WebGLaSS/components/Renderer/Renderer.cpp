#include "Renderer.hpp"

Renderer::Renderer() {
    WebGLaSS::renderPipeline.addRenderer(this);
}

void Renderer::preRenderCheck() {
    if (!this->pipelineId && this->pipelineId != 0) {
        throw new RenderPipelineNotAssignedException();
    }
}

void Renderer::render(bool useMaterial) { }

void Renderer::setId(unsigned int id) {
    this->pipelineId = id;
}

unsigned int Renderer::getId() {
    return this->pipelineId;
}

void Renderer::update() {
    
}