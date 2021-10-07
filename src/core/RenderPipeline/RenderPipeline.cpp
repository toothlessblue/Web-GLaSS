#include "RenderPipeline.hpp"

RenderPipeline::RenderPipeline() {
    std::cout << "Creating render pipeline" << std::endl;

    glGenVertexArrays(1, &this->vertexArray);
    glBindVertexArray(this->vertexArray);
    
    glm::vec3 quadVertices[6] = {
        glm::vec3(1, 0, 0),
        glm::vec3(0, 1, 0),
        glm::vec3(0, 0, 0),
        glm::vec3(1, 0, 0),
        glm::vec3(1, 1, 0),
        glm::vec3(0, 1, 0),
    };

    glBindBuffer(GL_ARRAY_BUFFER, this->quadVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec3), &quadVertices[0], GL_STATIC_DRAW);
    this->quadProgram = Shaders::CreateProgram("/shaders/RenderQuad.vert", "/shaders/RenderQuad.frag");

    glGenFramebuffers(1, &this->geometryBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, this->geometryBuffer);

    // - position color buffer
    glGenTextures(1, &this->gPosition);
    glBindTexture(GL_TEXTURE_2D, this->gPosition);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, GameEngine::screen.width, GameEngine::screen.height, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->gPosition, 0);
    
    // - normal color buffer
    glGenTextures(1, &this->gNormal);
    glBindTexture(GL_TEXTURE_2D, this->gNormal);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, GameEngine::screen.width, GameEngine::screen.height, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, this->gNormal, 0);
    
    // - color + specular color buffer
    glGenTextures(1, &this->gColorSpec);
    glBindTexture(GL_TEXTURE_2D, this->gColorSpec);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, GameEngine::screen.width, GameEngine::screen.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, this->gColorSpec, 0);

    unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
    glDrawBuffers(3, attachments);
}

RenderPipeline::~RenderPipeline() {
    for (Renderer *renderer : this->renderers) {
        delete renderer;
    }
}

void RenderPipeline::render() {
    // First, the geometry pass

    glBindFramebuffer(GL_FRAMEBUFFER, this->geometryBuffer); // Bind the geometry buffer
    glClearColor(0.0, 0.0, 0.0, 1.0); // keep it black so it doesn't leak into g-buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glm::mat4 view = this->activeCamera->getViewMatrix();
    glm::mat4 projection = this->activeCamera->getProjectionMatrix();

    for (Renderer *renderer : this->renderers) {
        glm::mat4 modelMatrix = renderer->gameObject->transform->getModelMatrix();

        renderer->material->setMat4("projectionMatrix", projection);
        renderer->material->setMat4("viewMatrix", view);
        renderer->material->setMat4("modelMatrix", modelMatrix);

        renderer->preRenderCheck();
        renderer->render();
    }
    
    // second pass
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
    glClear(GL_COLOR_BUFFER_BIT);
    
    glUseProgram(this->quadProgram);
    glBindVertexArray(this->vertexArray);
    glDisable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_2D, this->gColorSpec);
    glDrawArrays(GL_TRIANGLES, 0, 6);  
}

unsigned int RenderPipeline::addRenderer(Renderer* renderer) {
    this->renderers.push_back(renderer);

    unsigned int index = this->renderers.size() - 1;
    renderer->setId(index);
    return index;
}

void RenderPipeline::setActiveCamera(Camera* camera) {
    this->activeCamera = camera;
}