#pragma once

#include <GL/glew.h>
#include <list>

// Forward declarations
class Renderer;

class RenderPipeline {
public:
    GLuint mvpMatrixId;

    std::list<Renderer*> renderers;

	RenderPipeline(int openGLESVersion = 2);
	~RenderPipeline();

	void render();

    /**
     * Adds a renderer to this pipelines list, and returns its index
    */
    unsigned int addRenderer(Renderer* renderer);
};

#include "../components/Renderer/Renderer.hpp"