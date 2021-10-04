#pragma once
#include "../../core/Component/Component.hpp"

class CameraMouseController : public Component {
public:
    void update();

private:
    glm::vec3 lookVector;
};