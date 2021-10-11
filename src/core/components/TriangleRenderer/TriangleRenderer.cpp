#include "TriangleRenderer.hpp"

TriangleRenderer::TriangleRenderer() {
    this->mesh = ModelLoader::OBJ::loadMesh("/models/cube.obj");
}

void TriangleRenderer::render() {
    this->material->use();
    
    // TODO work out this instead https://stackoverflow.com/questions/42411310/do-i-have-to-call-glvertexattribpointer-each-frame-for-each-rendered-mesh

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, this->mesh->vertexBuffer);
    glVertexAttribPointer(
        0,                    // attribute 0
        3,                    // size - vec3
        GL_FLOAT,             // type
        GL_FALSE,             // normalized?
        0,                    // stride
        (void*)0              // array buffer offset
    );

    glBindBuffer(GL_ARRAY_BUFFER, this->mesh->uvBuffer);
    glVertexAttribPointer(
        1,                    // attribute 1
        2,                    // size - vec2
        GL_FLOAT,             // type
        GL_FALSE,             // normalized?
        0,                    // stride
        (void*)0              // array buffer offset
    );

    glBindBuffer(GL_ARRAY_BUFFER, this->mesh->normalsBuffer);
    glVertexAttribPointer(
        2,                    // attribute 2
        3,                    // size - vec3
        GL_FLOAT,             // type
        GL_FALSE,             // normalized?
        0,                    // stride
        (void*)0              // array buffer offset
    );

    // Draw the triangles !
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->mesh->indexesBuffer);
    glDrawElements(
        GL_TRIANGLES,               // mode
        this->mesh->indexes.size(), // count
        GL_UNSIGNED_INT,            // type
        (void*)0                    // element array buffer offset
    );

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}

void TriangleRenderer::update() {

}