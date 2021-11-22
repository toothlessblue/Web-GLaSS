#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../GameEngine/GameEngine.hpp"
#include "../components/Renderer/Renderer.hpp"
#include "../Mesh/Mesh.hpp"
#include "../Material/Material.hpp"
#include "../Shaders/Shaders.hpp"
#include <vector>

namespace Lighting {
    void initialise();

    class PointLight : public Component {
    public:
        PointLight();
        void start() override;

        void renderSceneToShadowDepthCubemap();
        void recalculateRadius();

        GLuint shadowCubemap;
        glm::mat4 shadowProjection;
        glm::mat4 shadowTransforms[6];

        glm::vec3 colour = glm::vec3(1,1,1);
        float constant = 0.5f;
        float linear = 0.5f;
        float quadratic = 0.5f;
        float radius;
    };

    void renderPointLightShadows();
    void renderPointLights(GLuint positionTex, GLuint normalTex, GLuint albedoTex);
    void renderAmbient(float power, GLuint positionTex, GLuint normalTex, GLuint albedoTex);

    extern Mesh* pointLightMesh;
    extern Material* pointLightMaterial;
    extern Material* pointLightShadowCubemapMaterial;
    extern std::vector<PointLight*> pointLights;
}