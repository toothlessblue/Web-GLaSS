#include "Lighting.hpp"

namespace Lighting {
    Mesh* pointLightMesh;
    Material* pointLightMaterial;
    Material* pointLightShadowCubemapMaterial;
    Material* ambientMaterial;
    std::vector<PointLight*> pointLights;

    void initialise() {
        Lighting::pointLightMesh = PrimitiveMeshes::generateSphereMesh(10, 10, 1);
        Lighting::ambientMaterial = new Material("/shaders/RenderQuad.vert", "/shaders/AmbientLighting.frag");
        Lighting::pointLightMaterial = new Material("/shaders/PointLightShader.vert", "/shaders/PointLightShader.frag");
        Lighting::pointLightShadowCubemapMaterial = new Material("/shaders/PointLightShadowDepth.vert", "/shaders/PointLightShadowDepth.frag");

        Lighting::pointLightMaterial->use();
        Lighting::pointLightMaterial->setInt("gPosition", 3);
        Lighting::pointLightMaterial->setInt("gNormal", 4);
        Lighting::pointLightMaterial->setInt("gAlbedo", 5);
        Lighting::pointLightMaterial->setFloat("screenWidth", WebGLaSS::screen.width);
        Lighting::pointLightMaterial->setFloat("screenHeight", WebGLaSS::screen.height);
        Lighting::pointLightMaterial->setInt("shadowCubemap", 6);
        
        Lighting::ambientMaterial->use();
        Lighting::ambientMaterial->setInt("gPosition", 3);
        Lighting::ambientMaterial->setInt("gNormal", 4);
        Lighting::ambientMaterial->setInt("gAlbedo", 5);
        Lighting::ambientMaterial->setFloat("power", 0.2f);
        Lighting::ambientMaterial->setFloat("screenWidth", WebGLaSS::screen.width);
        Lighting::ambientMaterial->setFloat("screenHeight", WebGLaSS::screen.height);

        glUseProgram(0);
    }

    PointLight::PointLight() {
        Lighting::pointLights.push_back(this);

        // Generate the cubemap
        glGenTextures(1, &this->shadowCubemap);

        glBindTexture(GL_TEXTURE_CUBE_MAP, this->shadowCubemap);
        for (unsigned int i = 0; i < 6; ++i) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT32F,  Shadows::resolution, Shadows::resolution, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);  
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

        this->recalculateRadius();
    }

    void PointLight::start() {
        this->shadowProjection = glm::perspective(glm::radians(90.0f), 1.0f, Shadows::nearPlane, Shadows::farPlane); 

        this->shadowTransforms[0] = this->shadowProjection * glm::lookAt(this->gameObject->transform->getPosition(), this->gameObject->transform->getPosition() + glm::vec3( 1.0, 0.0, 0.0), glm::vec3(0.0,-1.0, 0.0));
        this->shadowTransforms[1] = this->shadowProjection * glm::lookAt(this->gameObject->transform->getPosition(), this->gameObject->transform->getPosition() + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0,-1.0, 0.0));
        this->shadowTransforms[2] = this->shadowProjection * glm::lookAt(this->gameObject->transform->getPosition(), this->gameObject->transform->getPosition() + glm::vec3( 0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0));
        this->shadowTransforms[3] = this->shadowProjection * glm::lookAt(this->gameObject->transform->getPosition(), this->gameObject->transform->getPosition() + glm::vec3( 0.0,-1.0, 0.0), glm::vec3(0.0, 0.0,-1.0));
        this->shadowTransforms[4] = this->shadowProjection * glm::lookAt(this->gameObject->transform->getPosition(), this->gameObject->transform->getPosition() + glm::vec3( 0.0, 0.0, 1.0), glm::vec3(0.0,-1.0, 0.0));
        this->shadowTransforms[5] = this->shadowProjection * glm::lookAt(this->gameObject->transform->getPosition(), this->gameObject->transform->getPosition() + glm::vec3( 0.0, 0.0,-1.0), glm::vec3(0.0,-1.0, 0.0));
    }

    void PointLight::recalculateRadius() {
        float lightMax = std::fmaxf(std::fmaxf(this->colour.r, this->colour.g), this->colour.b);
        this->radius = (-linear + std::sqrtf(linear * linear - 4 * quadratic * (constant - (256.0 / 5.0) * lightMax))) / (2 * quadratic);  
    }

    void PointLight::renderSceneToShadowDepthCubemap() {
        // Assumes shadow FBO is bound

        Lighting::pointLightShadowCubemapMaterial->use();
        Lighting::pointLightShadowCubemapMaterial->setVec3("lightPosition", this->gameObject->transform->getPosition());

        for (unsigned int i = 0; i < 6; i++) {
            GLenum face = GL_TEXTURE_CUBE_MAP_POSITIVE_X + i;
            glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, face, this->shadowCubemap, 0);
            glClear(GL_DEPTH_BUFFER_BIT);

            Lighting::pointLightShadowCubemapMaterial->setMat4("shadowMatrix", this->shadowTransforms[i]);

            // Draw the actual scene to the frame buffer
            for (Renderer* renderer : WebGLaSS::renderPipeline.renderers) {
                if (!renderer->gameObject->isActive() || !renderer->isActive()) continue;

                Lighting::pointLightShadowCubemapMaterial->setMat4("modelMatrix", renderer->gameObject->transform->getModelMatrix());

                renderer->preRenderCheck();
                renderer->render(false);
            }
        }
    }

    void renderPointLightShadows() {
        glViewport(0, 0, Shadows::resolution, Shadows::resolution);
        glBindFramebuffer(GL_FRAMEBUFFER, Shadows::depthmapFramebuffer);
        glDrawBuffers(0, { GL_NONE });
        glReadBuffer(GL_NONE);


        Lighting::pointLightShadowCubemapMaterial->setFloat("farPlane", Shadows::farPlane);

        for (PointLight* pointLight : Lighting::pointLights) {
            pointLight->renderSceneToShadowDepthCubemap();
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, WebGLaSS::screen.width, WebGLaSS::screen.height);
    }

    void renderPointLights(GLuint gPosition, GLuint gNormal, GLuint gAlbedo) {
        glBindBuffer(GL_ARRAY_BUFFER, Lighting::pointLightMesh->vertexBuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); // vertices
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Lighting::pointLightMesh->indexBuffer);

        glCullFace(GL_FRONT);

        Lighting::pointLightMaterial->use();
        Lighting::pointLightMaterial->setVec3("viewPos", WebGLaSS::renderPipeline.activeCamera->gameObject->transform->getPosition());
        Lighting::pointLightMaterial->setMat4("viewMatrix", WebGLaSS::renderPipeline.activeCamera->getViewMatrix());
        Lighting::pointLightMaterial->setMat4("projectionMatrix", WebGLaSS::renderPipeline.activeCamera->getProjectionMatrix());

        Lighting::pointLightMaterial->setFloat("shadowFarPlane", Shadows::farPlane);

        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, gPosition);
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, gNormal);
        glActiveTexture(GL_TEXTURE5);
        glBindTexture(GL_TEXTURE_2D, gAlbedo);
        glActiveTexture(GL_TEXTURE6);

        for (PointLight* pointLight : Lighting::pointLights) {
            glBindTexture(GL_TEXTURE_CUBE_MAP, pointLight->shadowCubemap);
            
            Lighting::pointLightMaterial->setMat4("modelMatrix", pointLight->gameObject->transform->getModelMatrix());

            // TODO use a uniform buffer, it'll be faster
            Lighting::pointLightMaterial->setFloat("radius",      pointLight->radius);
            Lighting::pointLightMaterial->setVec3( "position",    pointLight->gameObject->transform->getPosition());
            Lighting::pointLightMaterial->setVec3( "lightColour", pointLight->colour);
            Lighting::pointLightMaterial->setFloat("constant",    pointLight->constant);
            Lighting::pointLightMaterial->setFloat("linear",      pointLight->linear);
            Lighting::pointLightMaterial->setFloat("quadratic",   pointLight->quadratic);

            glDrawElements(GL_TRIANGLES, Lighting::pointLightMesh->indexes.size(), GL_UNSIGNED_INT, (void*)0);
        }

        Lighting::pointLightMaterial->unuse();
        glCullFace(GL_BACK);
    }

    void renderAmbient(float power, GLuint gPosition, GLuint gNormal, GLuint gAlbedo) {
        Lighting::ambientMaterial->use();
        Lighting::ambientMaterial->setFloat("power", power);
        
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, gPosition);
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, gNormal);
        glActiveTexture(GL_TEXTURE5);
        glBindTexture(GL_TEXTURE_2D, gAlbedo);

        WebGLaSS::renderPipeline.bindRenderQuad();
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
}