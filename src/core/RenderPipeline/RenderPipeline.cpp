#include "RenderPipeline.hpp"

RenderPipeline::RenderPipeline() {
    std::cout << "Creating render pipeline" << std::endl;

    glGenVertexArrays(1, &this->quadVao);
    glBindVertexArray(this->quadVao);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &this->quadUvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->quadUvBuffer);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glBufferData(GL_ARRAY_BUFFER, sizeof(this->quadUvs), &this->quadUvs[0], GL_STATIC_DRAW);
    
    glGenBuffers(1, &this->quadVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->quadVertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glBufferData(GL_ARRAY_BUFFER, sizeof(this->quadVertices), &this->quadVertices[0], GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    this->quadProgram = Shaders::CreateProgram("/shaders/RenderQuad.vert", "/shaders/LightingPass.frag");
    glUseProgram(this->quadProgram);
    glUniform1i(glGetUniformLocation(this->quadProgram, "gPosition"), 3);
    glUniform1i(glGetUniformLocation(this->quadProgram, "gNormal"), 4);
    glUniform1i(glGetUniformLocation(this->quadProgram, "gAlbedo"), 5);

    std::cout << "Created render quad" << std::endl;

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
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->rbo);
    
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "Frame buffer incomplete" << std::endl;
    }

    std::cout << "Render pipeline constructed" << std::endl;
}

RenderPipeline::~RenderPipeline() {
    for (Renderer *renderer : this->renderers) {
        delete renderer;
    }
}

void RenderPipeline::render() {
    // Set up for drawing to the frame buffer

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->geometryBuffer); // Bind the geometry buffer
    glClearColor(0.0, 0.0, 0.0, 1.0); // keep it black so it doesn't leak into g-buffer
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw the actual scene to the frame buffer

    glm::mat4 view = this->activeCamera->getViewMatrix();
    glm::mat4 projection = this->activeCamera->getProjectionMatrix();

    for (Renderer* renderer : this->renderers) {
        glm::mat4 modelMatrix = renderer->gameObject->transform->getModelMatrix();

        renderer->material->setMat4("projectionMatrix", projection);
        renderer->material->setMat4("viewMatrix", view);
        renderer->material->setMat4("modelMatrix", modelMatrix);

        renderer->preRenderCheck();
        renderer->render();
    }
    
    // Prepare lighting pass on default frame buffer

    glBindVertexArray(this->quadVao);
    glUseProgram(this->quadProgram);

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, this->geometryBuffer);
    glDisable(GL_DEPTH_TEST);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Apply textures

    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, this->gPosition);
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, this->gNormal);
    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_2D, this->gAlbedo);

    // TODO send lighting information to program
    // TODO send view position to program

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);
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