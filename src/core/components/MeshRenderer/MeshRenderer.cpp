#include "MeshRenderer.hpp"

MeshRenderer::MeshRenderer() {
    // this->mesh = PrimitiveMeshes::generateSphereMesh(20, 20, 1.0f);
    this->mesh = ModelLoader::OBJ::loadMesh("/models/cube.obj");
}

void MeshRenderer::render() {
    if (!this->mesh) {
        std::cerr << "MeshRenderer does not have a mesh assigned" << std::endl;
    }
    
    if (!this->material) {
        std::cerr << "MeshRenderer does not have a material assigned" << std::endl;
    }

    this->material->use();
    
    this->mesh->bindMesh();
    glDrawElements(GL_TRIANGLES, this->mesh->indexes.size(), GL_UNSIGNED_INT, (void*)0);
    this->mesh->unbindMesh();

    this->material->unuse();
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
