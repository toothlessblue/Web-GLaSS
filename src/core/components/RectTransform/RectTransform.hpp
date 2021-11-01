#pragma once
#include "../../components/Transform/Transform.hpp"
#include "../include/glm/glm.hpp"

class RectTransform : public Transform {
public:
    RectTransform();

    void update() override;
    glm::vec2 calculatePosition();
    
    glm::vec2 anchorMin;
    glm::vec2 anchorMax;

    
};

