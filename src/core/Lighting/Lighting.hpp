#pragma once
#include "../Component/Component.hpp"
#include <list>

namespace Lighting {
    class Light : public Component {
    public:
        Light();
        
        bool enabled = true;
    };

    class PointLight : public Light {
    public:
        PointLight();
        
        // If true, light power is divided by (distance), if false, light power is divided by (distance * distance)
        bool linearlyDiminishLight = false; 
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

    extern std::list<Light*> lights;
}