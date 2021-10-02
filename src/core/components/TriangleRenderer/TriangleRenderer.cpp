#include <iostream>
#include <GL/glew.h>

#include "TriangleRenderer.hpp"

TriangleRenderer::TriangleRenderer() {
    glGenVertexArrays(1, &this->vertexArrayID);
    glGenBuffers(1, &this->vertexbuffer); // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer); // The following commands will talk about our 'vertexbuffer' buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(this->g_vertex_buffer_data), this->g_vertex_buffer_data, GL_STATIC_DRAW); // Give our vertices to OpenGL.
    
    glGenVertexArrays(1, &this->uvArrayID);
    glGenBuffers(1, &this->uvbuffer); // Generate 1 buffer, put the resulting identifier in uvbuffer
    glBindBuffer(GL_ARRAY_BUFFER, this->uvbuffer); // The following commands will talk about our 'uvbuffer' buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(this->g_uv_buffer_data), this->g_uv_buffer_data, GL_STATIC_DRAW); // Give our uvs to OpenGL.
}

void TriangleRenderer::render() {
    this->material->use();

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
    glVertexAttribPointer(
        0,                    // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                    // size
        GL_FLOAT,             // type
        GL_FALSE,             // normalized?
        0,                    // stride
        (void*)0              // array buffer offset
    );

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, this->uvbuffer);
    glVertexAttribPointer(
        1,                    // attribute 1
        2,                    // size
        GL_FLOAT,             // type
        GL_FALSE,             // normalized?
        0,                    // stride
        (void*)0              // array buffer offset
    );

    // Draw the triangles!
    glDrawArrays(GL_TRIANGLES, 0, (int)(sizeof(this->g_vertex_buffer_data)/sizeof(*this->g_vertex_buffer_data)) / 3);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}