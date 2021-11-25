#include "RenderPipelineNotAssignedException.hpp"

const char* RenderPipelineNotAssignedException::what() const throw() {
	return "This renderer has not been added to a render pipeline, and so render cannot be called.\nRender should not be called by anything except a pipeline.";
};