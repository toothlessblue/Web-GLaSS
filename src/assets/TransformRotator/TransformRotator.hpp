#pragma once
#include "../../core/Component/Component.hpp"
#include "../../core/GameObject/GameObject.hpp"
#include "../../core/Time/Time.hpp"

class TransformRotator : public Component {
public:
    TransformRotator();
    void update() override;
};
