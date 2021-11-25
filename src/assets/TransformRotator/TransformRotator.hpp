#pragma once
#include "../../Engine/Component/Component.hpp"
#include "../../Engine/GameObject/GameObject.hpp"
#include "../../Engine/Time/Time.hpp"

class TransformRotator : public Component {
public:
    TransformRotator();
    void update() override;
};
