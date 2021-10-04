#pragma once
#include "../../Component/Component.hpp"
#include "../../Input/Input.hpp"
#include "../../../../include/glm/glm.hpp"

class CameraMouseController : public Component {
public:
    void update();

private:
    glm::vec3 lookVector;
};