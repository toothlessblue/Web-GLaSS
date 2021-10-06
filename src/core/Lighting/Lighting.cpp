#include "Lighting.hpp"

namespace Lighting {
    // TODO this list of pointers needs a check for any pointers to deleted objects
    std::list<Light*> lights;

    Light::Light() {
        Lighting::lights.push_back(this);
    }
}