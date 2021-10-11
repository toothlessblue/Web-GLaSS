#include "Lighting.hpp"

namespace Lighting {
    // TODO this list of pointers needs a check for any pointers to deleted objects
    std::vector<PointLight*> pointLights;
    std::vector<DirectionalLight*> directionalLights;
    std::vector<OmnidirectionalLight*> omniDirectionalLights;
    
    GLuint lightProgram;
    GLuint lightUBO;
    GLuint uniformLightBlock;

    Light::Light() {
        
    }

    PointLight::PointLight() {
        Lighting::pointLights.push_back(this);
    }

    DirectionalLight::DirectionalLight() {
        Lighting::directionalLights.push_back(this);
    }

    OmnidirectionalLight::OmnidirectionalLight() {
        Lighting::omniDirectionalLights.push_back(this);
    }

    /**
     * Compiles the lighting shader program
     */
    void load() {
        Lighting::lightProgram = Shaders::CreateProgram("/shaders/RenderQuad.vert", "/shaders/LightingPass.frag");
        Lighting::uniformLightBlock = glGetUniformBlockIndex(Lighting::lightProgram, "lights");
        
        glGenBuffers(1, &Lighting::lightUBO);
    }

    void constructLightingUBO() {
        int maxLightsPerType = 50; // Must match array size within LightingPass.frag

        int pointLightSize = sizeof(float) * 11;
        int pointLightArraySize = pointLightSize * maxLightsPerType;

        int spotLightSize = sizeof(float) * 14;
        int spotLightArraySize = spotLightSize * maxLightsPerType;

        int directionalLightSize = sizeof(float) * 7;
        int directionalLightArraySize = directionalLightSize * maxLightsPerType;

        glBindBuffer(GL_UNIFORM_BUFFER, Lighting::lightUBO);
        glBufferData(
            GL_UNIFORM_BUFFER,
            pointLightArraySize + spotLightArraySize + directionalLightArraySize,
            NULL,
            GL_STREAM_DRAW
        );

        // TODO write lights to shader, keeping track of offset and skipping where neededs
    }

    void renderLights() {
        glUseProgram(Lighting::lightProgram);
    }
}