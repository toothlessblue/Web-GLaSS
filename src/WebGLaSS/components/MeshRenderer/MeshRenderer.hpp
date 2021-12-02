#pragma once

#include <GL/glew.h>
#include <iosfwd>
#include "../Renderer/Renderer.hpp"
#include "../../Mesh/Mesh.hpp"
#include "../../ModelLoader/ModelLoader.hpp"

/**
 * Renders a hardcoded list of vertices
 */
class MeshRenderer : public Renderer {
public:
    MeshRenderer();
    ~MeshRenderer();

    void render(bool useMaterial = true) override;
    void update() override;
    void deleteMesh();
    void setMesh(Mesh* mesh);
private:

    Mesh* mesh;
};