#include "Renderer.hpp"
#include "../../GameEngine/GameEngine.hpp"
#include <exception>

struct RenderPipelineNotAssignedException: public std::exception {
    const char* what() const throw() { 
	   return "This renderer has not been added to a render pipeline, and so render cannot be called.\nRender should not be called by anything except a pipeline.";
	}
};

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