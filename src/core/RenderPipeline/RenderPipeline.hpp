#pragma once

#include <GL/glew.h>
#include <list>
#include "../components/Renderer/Renderer.hpp"

class RenderPipeline {
public:
    GLuint programID;
    GLuint mvpMatrixId;

    std::list<Renderer*> renderers;

	RenderPipeline();
    void setProgram(GLuint programID);
	void render();

    /**
     * Adds a renderer to this pipelines list, and returns its index
    */
    unsigned int addRenderer(Renderer* renderer);
};