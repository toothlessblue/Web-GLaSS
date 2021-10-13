#pragma once

#include <GL/glew.h>
#include <iostream>
#include "../Renderer/Renderer.hpp"
#include "../../Mesh/Mesh.hpp"
#include "../../ModelLoader/ModelLoader.hpp"

/**
 * Renders a hardcoded list of vertices
 */
class TriangleRenderer : public Renderer {
public:
    TriangleRenderer();

    void render() override;
    void update() override;
private:
    Mesh* mesh;
    GLuint vao;
};