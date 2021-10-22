#include "Lighting.hpp"

namespace Lighting {
    Mesh* pointLightMesh;
    Material* pointLightMaterial;
    std::vector<PointLight*> pointLights;

    void initialise() {
        Lighting::pointLightMesh = PrimitiveMeshes::generateSphereMesh(10, 10, 1);
        Lighting::pointLightMaterial = new Material("/shaders/PointLightShader.vert", "/shaders/PointLightShader.frag");

        Lighting::pointLightMaterial->use();
        glUniform1i(glGetUniformLocation(Lighting::pointLightMaterial->shaderProgramId, "gPosition"), 3);
        glUniform1i(glGetUniformLocation(Lighting::pointLightMaterial->shaderProgramId, "gNormal"), 4);
        glUniform1i(glGetUniformLocation(Lighting::pointLightMaterial->shaderProgramId, "gAlbedo"), 5);
        glUseProgram(0);
    }

    PointLight::PointLight() {
        Lighting::pointLights.push_back(this);

        this->recalculateRadius();
    }

    void PointLight::recalculateRadius() {
        float lightMax = std::fmaxf(std::fmaxf(this->colour.r, this->colour.g), this->colour.b);
        this->radius = (-linear + std::sqrtf(linear * linear - 4 * quadratic * (constant - (256.0 / 5.0) * lightMax))) / (2 * quadratic);  
    }

    void renderPointLights(GLuint gPosition, GLuint gNormal, GLuint gAlbedo) {
        glBindBuffer(GL_ARRAY_BUFFER, Lighting::pointLightMesh->vertexBuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); // vertices
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Lighting::pointLightMesh->indexBuffer);

        glCullFace(GL_FRONT);

        Lighting::pointLightMaterial->use();
        Lighting::pointLightMaterial->setVec3("viewPos", GameEngine::renderPipeline.activeCamera->gameObject->transform->position);
        Lighting::pointLightMaterial->setMat4("viewMatrix", GameEngine::renderPipeline.activeCamera->getViewMatrix());
        Lighting::pointLightMaterial->setMat4("projectionMatrix", GameEngine::renderPipeline.activeCamera->getProjectionMatrix());

        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, gPosition);
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, gNormal);
        glActiveTexture(GL_TEXTURE5);
        glBindTexture(GL_TEXTURE_2D, gAlbedo);

        for (PointLight* pointLight : Lighting::pointLights) {
            Lighting::pointLightMaterial->setMat4("modelMatrix", pointLight->gameObject->transform->getModelMatrix());

            // TODO use a uniform buffer, it'll be faster
            Lighting::pointLightMaterial->setFloat("radius", pointLight->radius);
            Lighting::pointLightMaterial->setVec3("position", pointLight->gameObject->transform->position);
            Lighting::pointLightMaterial->setVec3("colour", pointLight->colour);
            Lighting::pointLightMaterial->setFloat("constant", pointLight->constant);
            Lighting::pointLightMaterial->setFloat("linear", pointLight->linear);
            Lighting::pointLightMaterial->setFloat("quadratic", pointLight->quadratic);

            glDrawElements(GL_TRIANGLES, Lighting::pointLightMesh->indexes.size(), GL_UNSIGNED_INT, (void*)0);
        }

        glUseProgram(0);
        glCullFace(GL_BACK);
    }
}