#pragma once
#include "../../core/Component/Component.hpp"
#include "../../core/Input/Input.hpp"

class FloatingCameraKeyboardController : public Component {
public:
    float speed = 5.0f;

    FloatingCameraKeyboardController();

    void update();
private:

};
