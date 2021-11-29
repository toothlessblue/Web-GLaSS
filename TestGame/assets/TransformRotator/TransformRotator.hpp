#pragma once
#include "../../../src/WebGLaSS/Component/Component.hpp"
#include "../../../src/WebGLaSS/GameObject/GameObject.hpp"
#include "../../../src/WebGLaSS/Time/Time.hpp"

class TransformRotator : public Component {
public:
    TransformRotator();
    void update() override;
};
