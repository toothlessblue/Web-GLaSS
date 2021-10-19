#include "MeshRenderer.hpp"

void MeshRenderer::bindMesh() {
    glBindBuffer(GL_ARRAY_BUFFER, this->mesh->vertexBuffer);
    glVertexAttribPointer(
        0,                    // attribute 0
        3,                    // size - vec3
        GL_FLOAT,             // type
        GL_FALSE,             // normalized?
        8 * sizeof(float),    // stride
        (void*)0              // array buffer offset
    );

    glVertexAttribPointer(
        1,                    // attribute 1
        3,                    // size - vec3
        GL_FLOAT,             // type
        GL_FALSE,             // normalized?
        8 * sizeof(float),    // stride
        (void*)(3 * sizeof(float)) // array buffer offset
    );

    glVertexAttribPointer(
        2,                    // attribute 2
        2,                    // size - vec2
        GL_FLOAT,             // type
        GL_FALSE,             // normalized?
        8 * sizeof(float),    // stride
        (void*)(6 * sizeof(float)) // array buffer offset
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->mesh->indexBuffer);
}

void MeshRenderer::unbindMesh() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

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
    
    this->bindMesh();
    glDrawElements(GL_TRIANGLES, this->mesh->indexes.size(), GL_UNSIGNED_INT, (void*)0);
    this->unbindMesh();
}

void MeshRenderer::update() {

}

void MeshRenderer::deleteMesh() {
    delete this->mesh;
}

void MeshRenderer::setMesh(Mesh* mesh) {
    this->mesh = mesh;
}
