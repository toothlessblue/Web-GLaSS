#include "Renderer.hpp"

Renderer::Renderer() {
    GameEngine::renderPipeline.addRenderer(this);
}

void Renderer::preRenderCheck() {
    if (!this->pipelineId && this->pipelineId != 0) {
        throw new RenderPipelineNotAssignedException();
    }
}

void Renderer::render() { }

void Renderer::setId(unsigned int id) {
    this->pipelineId = id;
}

unsigned int Renderer::getId() {
    return this->pipelineId;
}

void Renderer::update() {
    
}