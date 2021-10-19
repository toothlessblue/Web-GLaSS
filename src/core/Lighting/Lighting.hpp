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

        void recalculateRadius();

        glm::vec3 colour = glm::vec3(1,1,1);
        float constant = 1.0f;
        float linear = 1.0f;
        float quadratic = 1.0f;
        float radius;
    };

    void renderPointLights(GLuint positionTex, GLuint normalTex, GLuint albedoTex);

    extern Mesh* pointLightMesh;
    extern Material* pointLightMaterial;
    extern std::vector<PointLight*> pointLights;
}