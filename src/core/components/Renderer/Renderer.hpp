#pragma once

#include <GL/glew.h>
#include "../../Component/Component.hpp"
#include "../../Material/Material.hpp"

class Renderer : public Component {
public:
    Material* material;

	Renderer();

	virtual void preRenderCheck();
	virtual void render();
    virtual void update() override;

	void setId(unsigned int id);
private:
	unsigned int pipelineId;
};