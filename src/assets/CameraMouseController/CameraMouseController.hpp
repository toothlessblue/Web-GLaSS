#pragma once
#include "../../core/Component/Component.hpp"
#include "../../../include/glm/glm.hpp"

class CameraMouseController : public Component {
public:
    void update();

private:
    glm::vec3 lookVector;
};