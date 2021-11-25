#pragma once
#include "../../Engine/Component/Component.hpp"
#include "../../../include/glm/glm.hpp"
#include "../../Engine/Input/Input.hpp"
#include "../../Engine/Time/Time.hpp"

class CameraMouseController : public Component {
public:
    void update();

private:
    glm::vec3 lookVector;
};