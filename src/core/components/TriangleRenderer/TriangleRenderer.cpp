#include "TriangleRenderer.hpp"

TriangleRenderer::TriangleRenderer() {
    this->mesh = ModelLoader::OBJ::loadMesh("/models/cube.obj");
}

void TriangleRenderer::render() {
    this->material->use();
    this->mesh->draw();
}

void TriangleRenderer::update() {

}