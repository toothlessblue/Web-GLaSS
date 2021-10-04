#pragma once

#include <GL/glew.h>
#include "../Renderer/Renderer.hpp"
#include "../../Mesh/Mesh.hpp"

/**
 * Renders a hardcoded list of vertices
 */
class TriangleRenderer : public Renderer {
public:
    TriangleRenderer();

    void render() override;
private:
    Mesh* mesh;

    unsigned int g_triangle_buffer_data[36] = { // Anticlockwise triangles, these triangles are wrong
        0, 1, 2, // Bottom face
        0, 2, 3,
    
        4, 5, 6, // Top face
        4, 6, 7,

        1, 2, 5, // Left
        2, 6, 5,

        0, 3, 4, // Right
        3, 7, 4,

        0, 1, 5, // Forward
        0, 5, 4,

        3, 2, 6, // Back
        6, 7, 3,
    };

    GLfloat g_vertex_buffer_data[24] = {
        -1.0, -1.0, -1.0,
        -1.0, -1.0, 1.0,
        1.0, -1.0, 1.0,
        1.0, -1.0, -1.0,
        -1.0, 1.0, -1.0,
        -1.0, 1.0, 1.0,
        1.0, 1.0, 1.0,
        1.0, 1.0, -1.0,
    };

    // Two UV coordinates for each vertex.
    GLfloat g_uv_buffer_data[72] = {
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