#pragma once

#include <GL/glew.h>
#include "../../Component/Component.hpp"
#include "../../Material/Material.hpp"
#include "../../GameEngine/GameEngine.hpp"
#include "../../Exceptions/RenderPipelineNotAssignedException.cpp"
#include "../../GameEngine/GameEngine.hpp"
#include "../../Exceptions/RenderPipelineNotAssignedException.cpp"

class Renderer : public Component {
public:
    Material* material = NULL;

	Renderer();

	virtual void preRenderCheck();
	virtual void render();
    virtual void update() override;

	void setId(unsigned int id);
	unsigned int getId();
private:
	unsigned int pipelineId;
};