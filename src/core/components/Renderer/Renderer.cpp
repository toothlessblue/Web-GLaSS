#include "Renderer.hpp"
#include <exception>

struct RenderPipelineNotAssignedException: public std::exception {
    const char* what() const throw() { 
	   return "This renderer has not been added to a render pipeline, and so render cannot be called.\nRender should not be called by anything except a pipeline.";
	}
};

Renderer::Renderer() {

}

void Renderer::preRenderCheck() {
    if (!this->pipelineId) {
        throw new RenderPipelineNotAssignedException();
    }
}

void Renderer::render() { }

void Renderer::setPipelineId(unsigned int id) {
    this->pipelineId = id;
}