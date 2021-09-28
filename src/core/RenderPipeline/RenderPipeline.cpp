#include "RenderPipeline.hpp"
#include <GL/glew.h>
#include "../../../include/glm/glm.hpp"
#include "../../../include/glm/gtx/transform.hpp"
#include "../../../include/glm/gtc/matrix_transform.hpp"

RenderPipeline::RenderPipeline() {
    // glEnable(GL_DEPTH_TEST); // OpenGL ES 1.0
    // glDepthFunc(GL_LESS);    // OpenGL ES 1.0
}

// TODO program class to handle that sort of information

void RenderPipeline::setProgram(GLuint programID) {
    this->programID = programID;
    this->mvpMatrixId = glGetUniformLocation(this->programID, "MVP_matrix");
}

void RenderPipeline::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clears the screen and depth buffer

    glUseProgram(this->programID); // TODO place this in render function of each renderer to allow seperate shaders for different renderers

    // TODO get view and projection matrices from active camera component
    glm::mat4 view = glm::lookAt(
        glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
        glm::vec3(0,0,0), // and looks at the origin
        glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 900.0f / 450.0f, 0.1f, 100.0f);

    for (Renderer *renderer : this->renderers) {
        glm::mat4 mvpMatrix = renderer->gameObject->transform->getModelViewProjectionMatrix(
            view,
            projection
        );

        // TODO this->currentProgram->mvpMatrixId
        glUniformMatrix4fv(this->mvpMatrixId, 1, GL_FALSE, &mvpMatrix[0][0]);

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