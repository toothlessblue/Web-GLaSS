#pragma once
#include "../../components/Transform/Transform.hpp"
#include "../include/glm/glm.hpp"
#include "../../GameEngine/GameEngine.hpp"
#include "../../Math/Math.hpp"

class RectTransform : public Transform {
public:
    RectTransform();

    void update() override;
    glm::vec2 calculatePosition();
    
    glm::vec2 anchorMin;
    glm::vec2 anchorMax;

    float width;
    float height;

    float getLeft();
    void setLeft(float v);
    float getRight();
    void setRight(float v);
    float getTop();
    void setTop(float v);
    float getBottom();
    void setBottom(float v);

    glm::vec2 getDimensions() override;
private:
    glm::vec2 getParentDimensions();
    glm::vec3 getParentPosition();
};

