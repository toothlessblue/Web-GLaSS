#include "Lighting.hpp"

namespace Lighting {
    // TODO this list of pointers needs a check for any pointers to deleted objects
    std::list<Light*> lights;
    GLuint lightsBufferId;
    
    Light::Light() {
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
}