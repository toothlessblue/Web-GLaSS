#include "Renderer2d.hpp"

Renderer2d::Renderer2d() {
    GameEngine::renderPipeline.addRenderer2d(this);
}

void Renderer2d::preRenderCheck() {
    if (!this->pipelineId && this->pipelineId != 0) {
        throw new RenderPipelineNotAssignedException();
    }
}

void Renderer2d::render() { }

void Renderer2d::setId(unsigned int id) {
    this->pipelineId = id;
}

unsigned int Renderer2d::getId() {
    return this->pipelineId;
}

void Renderer2d::update() {
    
}