#pragma once

#include "../../Component/Component.hpp"
#include "../../GameEngine/GameEngine.hpp"
#include "../../Exceptions/RenderPipelineNotAssignedException.cpp"

class Material;

/**
 * A parent class for rendering 2d elements, like UI. All 2d renderers are unlit, and rendered on top of 3d elements.
 */
class Renderer2d : public Component {
public:
    Material* material;

	Renderer2d();

	virtual void preRenderCheck();
	virtual void render();
    virtual void update() override;

	void setId(unsigned int id);
	unsigned int getId();
private:
	unsigned int pipelineId;
};