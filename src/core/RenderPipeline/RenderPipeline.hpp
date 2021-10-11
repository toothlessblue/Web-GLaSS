#pragma once

#include <list>
#include <GL/glew.h>
#include <iostream>
#include "../../../include/glm/glm.hpp"
#include "../../../include/glm/gtx/transform.hpp"
#include "../../../include/glm/gtc/matrix_transform.hpp"
#include "../components/Camera/Camera.hpp"
#include "../GameEngine/GameEngine.hpp"
#include "../Lighting/Lighting.hpp"
#include "../Shaders/Shaders.hpp"

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
    GLuint vertexArray;
    GLuint geometryBuffer, depthBuffer;
    GLuint gPosition, gNormal, gAlbedo;
    GLuint rbo;

    GLuint quadProgram, quadVertexBuffer, quadUvBuffer;

    const GLfloat quadVertices[18] = {
         1.0f,  1.0f,  0.0f,
        -1.0f, -1.0f,  0.0f,
        -1.0f,  1.0f,  0.0f,
         1.0f,  1.0f,  0.0f,
         1.0f, -1.0f,  0.0f,
        -1.0f, -1.0f,  0.0f,
    };

    const GLfloat quadUvs[12] = {
        1.0f, 1.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
    };
};

#include "../components/Renderer/Renderer.hpp"
#include "../components/Camera/Camera.hpp"