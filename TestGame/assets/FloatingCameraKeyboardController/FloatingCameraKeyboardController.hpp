#pragma once
#include "../../../src/WebGLaSS/Component/Component.hpp"
#include "../../../src/WebGLaSS/Input/Input.hpp"

class FloatingCameraKeyboardController : public Component {
public:
    float speed = 2.0f;

    FloatingCameraKeyboardController();

    void update();
private:

};
