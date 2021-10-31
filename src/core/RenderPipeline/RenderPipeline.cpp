#include "RenderPipeline.hpp"

RenderPipeline::RenderPipeline() {
    std::cout << "initialising lighting" << std::endl;

    Lighting::initialise();

    std::cout << "Creating render quad" << std::endl;

    glGenBuffers(1, &this->quadVertexBuffer);
    glGenBuffers(1, &this->quadUvBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, this->quadVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * 6, &this->quadVertices[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, this->quadUvBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 6, &this->quadUvs[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    std::cout << "Creating render pipeline" << std::endl;

    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

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
    glGenTextures(1, &this->gAlbedo);
    glBindTexture(GL_TEXTURE_2D, this->gAlbedo);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, GameEngine::screen.width, GameEngine::screen.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, this->gAlbedo, 0);

    GLenum attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
    glDrawBuffers(3, attachments);

    glGenRenderbuffers(1, &this->rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, this->rbo); 
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, GameEngine::screen.width, GameEngine::screen.height);  
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "Frame buffer incomplete" << std::endl;
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    std::cout << "Render pipeline constructed" << std::endl;

    glEnable(GL_CULL_FACE);
}

RenderPipeline::~RenderPipeline() {
    for (Renderer *renderer : this->renderers) {
        delete renderer;
    }
}

void RenderPipeline::renderLitToFrameBuffer(std::vector<unsigned int>* unlitRendererIds) {
    // Set up for drawing to the frame buffer

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->geometryBuffer); // Bind the geometry buffer
    glClearColor(0.0, 0.0, 0.0, 1.0); // keep it black so it doesn't leak into g-buffer
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw the actual scene to the frame buffer

    glm::mat4 view = this->activeCamera->getViewMatrix();
    glm::mat4 projection = this->activeCamera->getProjectionMatrix();

    for (Renderer* renderer : this->renderers) {
        if (renderer->material->unlit) {
            unlitRendererIds->push_back(renderer->getId());
            continue;
        }

        glm::mat4 modelMatrix = renderer->gameObject->transform->getModelMatrix();

        renderer->material->setMat4("projectionMatrix", projection);
        renderer->material->setMat4("viewMatrix", view);
        renderer->material->setMat4("modelMatrix", modelMatrix);

        renderer->preRenderCheck();
        renderer->render();
    }

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void RenderPipeline::render2dElements() {
    for (Renderer2d* renderer : this->renderers2d) {
        glm::mat4 modelMatrix = 
            glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, -1.0f, 0)) *
            glm::translate(renderer->gameObject->transform->position * 2.0f) * 
            renderer->gameObject->transform->getRotationMatrix() * 
            renderer->gameObject->transform->getScaleMatrix();

        renderer->material->setMat4("modelMatrix", modelMatrix);

        renderer->preRenderCheck();
        renderer->render();
    }
}

void RenderPipeline::render() {
    std::vector<unsigned int> unlitRendererIds;
    this->renderLitToFrameBuffer(&unlitRendererIds);

    glBindFramebuffer(GL_READ_FRAMEBUFFER, this->geometryBuffer);
    glDisable(GL_DEPTH_TEST);
    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    Lighting::renderPointLights(this->gPosition, this->gNormal, this->gAlbedo);
    Lighting::renderAmbient(0.2f, this->gPosition, this->gNormal, this->gAlbedo);

    // TODO render unlit materials. if I use this method I need to clear the frame buffer, render unlit materials to it, then render ambient lighting again

    this->render2dElements();
}

unsigned int RenderPipeline::addRenderer(Renderer* renderer) {
    this->renderers.push_back(renderer);

    unsigned int index = this->renderers.size() - 1;
    renderer->setId(index);
    return index;
}

unsigned int RenderPipeline::addRenderer2d(Renderer2d* renderer) {
    this->renderers2d.push_back(renderer);

    unsigned int index = this->renderers2d.size() - 1;
    renderer->setId(index);
    return index;
}

void RenderPipeline::setActiveCamera(Camera* camera) {
    this->activeCamera = camera;
}

/**
 * Binds render quad UVs and vertices to attrib pointers, 
 * leaves the vertex buffer bound to GL_ARRAY_BUFFER
 */
void RenderPipeline::bindRenderQuad() {
    glBindBuffer(GL_ARRAY_BUFFER, this->quadUvBuffer);
    glVertexAttribPointer(
        1,                    // attribute 0
        2,                    // size - vec2
        GL_FLOAT,             // type
        GL_FALSE,             // normalized?
        0,    // stride
        (void*)0              // array buffer offset
    );

    glBindBuffer(GL_ARRAY_BUFFER, this->quadVertexBuffer);
    glVertexAttribPointer(
        0,                    // attribute 1
        3,                    // size - vec3
        GL_FLOAT,             // type
        GL_FALSE,             // normalized?
        0,    // stride
        (void*)0 // array buffer offset
    );
}