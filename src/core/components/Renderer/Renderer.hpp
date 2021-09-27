#pragma once

#include <GL/glew.h>
#include "../../Component/Component.hpp"

class Renderer : public Component {
public:
	Renderer();

	virtual void preRenderCheck();
	virtual void render();

	void setId(unsigned int id);
private:
	unsigned int pipelineId;
};