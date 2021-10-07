#include "Lighting.hpp"

namespace Lighting {
    // TODO this list of pointers needs a check for any pointers to deleted objects
    std::vector<Light*> lights;
    
    Light::Light() {
        if (Lighting::lights.size() >= MAX_LIGHTS) {
            throw "Cannot add another light, light count is more than or equal to MAX_LIGHTS";
        }

        Lighting::lights.push_back(this);
    }

    PointLight::PointLight() {
        this->type = 0;
    }

    DirectionalLight::DirectionalLight() {
        this->type = 1;
    }

    OmnidirectionalLight::OmnidirectionalLight() {
        this->type = 2;
    }

    void sendLightsToCurrentShader() {
        for (int i = 0; i < Lighting::lights.size(); i++) {
            Light* light = Lighting::lights[i];

            // TODO push lights to uniform array
        }
    }
}