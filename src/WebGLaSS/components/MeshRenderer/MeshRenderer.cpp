#include "MeshRenderer.hpp"
#include <iostream>

MeshRenderer::MeshRenderer() {
    // this->mesh = PrimitiveMeshes::generateSphereMesh(20, 20, 1.0f);
    this->setMesh(ModelLoader::OBJ::loadMesh("/models/cube.obj"));
}

MeshRenderer::~MeshRenderer() { }

void MeshRenderer::render(bool useMaterial) {
    if (!this->mesh) {
        std::cerr << "MeshRenderer does not have a mesh assigned" << std::endl;
    }
    
    if (!this->material) {
        std::cerr << "MeshRenderer does not have a material assigned" << std::endl;
    }

    if (useMaterial) this->material->use();
    
    this->mesh->bindMesh();
    glDrawElements(GL_TRIANGLES, this->mesh->indexes.size(), GL_UNSIGNED_INT, (void*)0);
    this->mesh->unbindMesh();

    if (useMaterial) this->material->unuse();
}

void MeshRenderer::update() {

}

void MeshRenderer::deleteMesh() {
    delete this->mesh;
    this->mesh = NULL;
}

void MeshRenderer::setMesh(Mesh* mesh) {
    this->mesh = mesh;
}
