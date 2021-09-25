#pragma once

#include "../Renderer/Renderer.hpp"

class TriangleRenderer : public Renderer {
public:
    TriangleRenderer();

    void render() override;
private:
    GLuint vertexArrayID;
    GLuint vertexbuffer;

    const GLfloat g_vertex_buffer_data[9] = {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         0.0f,  1.0f, 0.0f,
    };
};