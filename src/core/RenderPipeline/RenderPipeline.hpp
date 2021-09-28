#pragma once

#include <GL/glew.h>
#include <list>

// Forward declarations
class Renderer;

class RenderPipeline {
public:
    GLuint programID;
    GLuint mvpMatrixId;

    std::list<Renderer*> renderers;

	RenderPipeline();
	~RenderPipeline();
    
    void setProgram(GLuint programID);
	void render();

    /**
     * Adds a renderer to this pipelines list, and returns its index
    */
    unsigned int addRenderer(Renderer* renderer);
};

#include "../components/Renderer/Renderer.hpp"