#include "TriangleRenderer.hpp"

TriangleRenderer::TriangleRenderer() {
    this->mesh = ModelLoader::OBJ::loadMesh("/models/cube.obj");

    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    for (int i = 0; i < 3; i++) {
        glEnableVertexAttribArray(i);
    }

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

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->mesh->indexesBuffer); // Bind vbo    1
    glBindVertexArray(0);                                             // unbind vao  2  This order matters
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);                         // unbind vbo  3
}

void TriangleRenderer::render() {
    this->material->use();
    
    glBindVertexArray(this->vao);
    glDrawElements(GL_TRIANGLES, this->mesh->indexes.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
}

void TriangleRenderer::update() {

}