#include "RenderPipeline.hpp"
#include <GL/glew.h>
#include "../../../include/glm/glm.hpp"
#include "../../../include/glm/gtx/transform.hpp"
#include "../../../include/glm/gtc/matrix_transform.hpp"
#include "../components/Camera/Camera.hpp"

RenderPipeline::RenderPipeline() {
    
}

RenderPipeline::~RenderPipeline() {
    for (Renderer *renderer : this->renderers) {
        delete renderer;
    }
}

void RenderPipeline::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clears the screen and depth buffer

    glm::mat4 view = this->activeCamera->getViewMatrix();
    glm::mat4 projection = this->activeCamera->getProjectionMatrix();

    for (Renderer *renderer : this->renderers) {
        glm::mat4 modelMatrix = renderer->gameObject->transform->getModelMatrix();
        glm::mat4 mvpMatrix = projection * view * modelMatrix;

        renderer->material->setMat4("MVP_matrix", mvpMatrix);

        renderer->preRenderCheck();
        renderer->render();
    }
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