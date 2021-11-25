#pragma once
#include <GL/glew.h>
#include "../../Component/Component.hpp"
#include "../../Material/Material.hpp"
#include "../../WebGLaSS.hpp"
#include "../../Exceptions/RenderPipelineNotAssignedException.hpp"

class Material;

class Renderer : public Component {
public:
    Material* material = NULL;

	Renderer();

	virtual void preRenderCheck();
	virtual void render(bool useMaterial = true);
    virtual void update() override;

	void setId(unsigned int id);
	unsigned int getId();
private:
	unsigned int pipelineId;
};