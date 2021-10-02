#pragma once

#include <GL/glew.h>
#include "../Renderer/Renderer.hpp"

/**
 * Renders a hardcoded list of vertices
 */
class TriangleRenderer : public Renderer {
public:
    TriangleRenderer();

    void render() override;
private:
    GLuint vertexArrayID;
    GLuint uvArrayID;
    
    GLuint vertexbuffer;
    GLuint uvbuffer;

    const GLfloat g_vertex_buffer_data[108] = {
       -1.0f,-1.0f,-1.0f, // triangle 1 : begin
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end
        1.0f, 1.0f,-1.0f, // triangle 2 : begin
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f, // triangle 2 : end
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f
    };

    // Two UV coordinates for each vertex.
    const GLfloat g_uv_buffer_data[72] = {
        0.000059f, 0.000004f,
        0.000103f, 0.336048f,
        0.335973f, 0.335903f,
        1.000023f, 0.000013f,
        0.667979f, 0.335851f,
        0.999958f, 0.336064f,
        0.667979f, 0.335851f,
        0.336024f, 0.671877f,
        0.667969f, 0.671889f,
        1.000023f, 0.000013f,
        0.668104f, 0.000013f,
        0.667979f, 0.335851f,
        0.000059f, 0.000004f,
        0.335973f, 0.335903f,
        0.336098f, 0.000071f,
        0.667979f, 0.335851f,
        0.335973f, 0.335903f,
        0.336024f, 0.671877f,
        1.000004f, 0.671847f,
        0.999958f, 0.336064f,
        0.667979f, 0.335851f,
        0.668104f, 0.000013f,
        0.335973f, 0.335903f,
        0.667979f, 0.335851f,
        0.335973f, 0.335903f,
        0.668104f, 0.000013f,
        0.336098f, 0.000071f,
        0.000103f, 0.336048f,
        0.000004f, 0.671870f,
        0.336024f, 0.671877f,
        0.000103f, 0.336048f,
        0.336024f, 0.671877f,
        0.335973f, 0.335903f,
        0.667969f, 0.671889f,
        1.000004f, 0.671847f,
        0.667979f, 0.335851f
    };
};