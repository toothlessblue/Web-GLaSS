#pragma once
#include "../../../include/glm/glm.hpp"
#include "../../../src/WebGLaSS/Component/Component.hpp"
#include "../../../src/WebGLaSS/Input/Input.hpp"
#include "../../../src/WebGLaSS/Time/Time.hpp"

class CameraMouseController : public Component {
public:
    void update();

private:
    glm::vec3 lookVector;
};