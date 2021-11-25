#pragma once
#include <list>
#include <GL/glew.h>
#include <iosfwd>
#include "../../../include/glm/glm.hpp"
#include "../../../include/glm/gtx/transform.hpp"
#include "../../../include/glm/gtc/matrix_transform.hpp"
#include "../components/Camera/Camera.hpp"
#include "../WebGLaSS.hpp"
#include "../Lighting/Lighting.hpp"
#include "../Shadows/Shadows.hpp"
#include "../Shaders/Shaders.hpp"

// Forward declarations
class Renderer;
class Renderer2d;
class Camera;

class RenderPipeline {
public:
    GLuint mvpMatrixId;
    Camera* activeCamera;

    std::list<Renderer*> renderers;
    std::list<Renderer2d*> renderers2d;

	RenderPipeline();
	~RenderPipeline();

	void render();

    /**
     * Adds a renderer to this pipelines list, and returns its index
    */
    unsigned int addRenderer(Renderer* renderer);
    unsigned int addRenderer2d(Renderer2d* renderer);

    void setActiveCamera(Camera* camera);

    void bindRenderQuad();
private:
    GLuint geometryBuffer, depthBuffer;
    GLuint gPosition, gNormal, gAlbedo;
    GLuint rbo;

    GLuint quadProgram, quadVertexBuffer, quadUvBuffer;

    GLuint vao;

    const GLfloat quadVertices[18] = {
         1.0f,  1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
         1.0f,  1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
    };

    const GLfloat quadUvs[12] = {
        1.0f, 1.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
    };

    void renderLitToCurrentFBO(std::vector<unsigned int>* unlitRendererIds);
    void render2dElements();
};

#include "../components/Renderer/Renderer.hpp"
#include "../components/Renderer2d/Renderer2d.hpp"
#include "../components/Camera/Camera.hpp"