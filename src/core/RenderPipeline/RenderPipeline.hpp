#pragma once

#include <GL/glew.h>
#include <list>

// Forward declarations
class Renderer;
class Camera;

class RenderPipeline {
public:
    GLuint mvpMatrixId;
    Camera* activeCamera;

    std::list<Renderer*> renderers;

	RenderPipeline();
	~RenderPipeline();

	void render();

    /**
     * Adds a renderer to this pipelines list, and returns its index
    */
    unsigned int addRenderer(Renderer* renderer);

    void setActiveCamera(Camera* camera);
private:
    GLuint geometryBuffer, depthBuffer;
    GLuint gPosition, gNormal, gColorSpec;
    GLuint lightingProgram;
};

#include "../components/Renderer/Renderer.hpp"
#include "../components/Camera/Camera.hpp"