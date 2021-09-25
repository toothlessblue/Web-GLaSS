#pragma once

#include "../Renderer/Renderer.hpp"

class MeshRenderer : public Renderer {
public:
	MeshRenderer();
	void render() override;
};