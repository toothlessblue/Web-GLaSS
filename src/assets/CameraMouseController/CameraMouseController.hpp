#pragma once
#include "../../core/Component/Component.hpp"
#include "../../../include/glm/glm.hpp"
#include "../../core/Input/Input.hpp"
#include "../../core/Time/Time.hpp"

class CameraMouseController : public Component {
public:
    void update();

private:
    glm::vec3 lookVector;
};