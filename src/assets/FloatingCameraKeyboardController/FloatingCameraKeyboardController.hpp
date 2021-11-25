#pragma once
#include "../../Engine/Component/Component.hpp"
#include "../../Engine/Input/Input.hpp"

class FloatingCameraKeyboardController : public Component {
public:
    float speed = 2.0f;

    FloatingCameraKeyboardController();

    void update();
private:

};
