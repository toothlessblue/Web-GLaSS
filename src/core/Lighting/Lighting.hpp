#pragma once
#define MAX_LIGHTS 128
#include "../Component/Component.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

namespace Lighting {
    /**
     * Asbtract base class, do not construct
     */
    class Light : public Component {
    public:
        Light();
        
        glm::vec3 colour;
        int type = -1; // Default value, immediately overriden in the constructors of other light classes.
    };

    /**
     * Lights up objects within a distance around it, good for things like lamps
     */
    class PointLight : public Light {
    public:
        PointLight();
        
        // If true, light intensity is divided by (distance), if false, light intensity is divided by (distance * distance)
        bool linearlyDiminishLight = false;
        float maxDistance;
    };

    /**
     * A global light source that casts shadows in the direction it's pointing
     * Good for day/night cycles or constant global light
     */
    class DirectionalLight : public Light {
    public:
        DirectionalLight();
    };

    /**
     * A PointLight that doesn't diminish over distance, useful for things like suns
     */
    class OmnidirectionalLight : public Light {
    public:
        OmnidirectionalLight();
    };

    extern std::vector<Light*> lights;
    extern GLuint lightsBufferId;

    void pushLightsToShaderProgram();
}