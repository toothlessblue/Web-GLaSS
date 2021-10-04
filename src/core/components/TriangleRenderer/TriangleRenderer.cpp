#include <iostream>
#include <GL/glew.h>

#include "TriangleRenderer.hpp"

TriangleRenderer::TriangleRenderer() {
    this->mesh = new Mesh();
    this->mesh->setVertices(&this->g_vertex_buffer_data[0], sizeof(this->g_vertex_buffer_data));
    this->mesh->setUVs(&this->g_uv_buffer_data[0], sizeof(this->g_uv_buffer_data));
    this->mesh->setTriangles(&this->g_triangle_buffer_data[0], sizeof(this->g_triangle_buffer_data));
}

void TriangleRenderer::render() {
    this->material->use();

    // Bind the vertexes of the triangles to render

    this->mesh->draw();
}