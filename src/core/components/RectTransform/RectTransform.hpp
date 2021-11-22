#pragma once
#include "../../../../include/glm/glm.hpp"
#include "../../GameEngine/GameEngine.hpp"
#include "../../Math/Math.hpp"
#include "../../components/Transform/Transform.hpp"

class RectTransform : public Transform {
public:
    RectTransform();

    void update() override;
    
    glm::vec2 anchorMin = glm::vec2(0, 0);
    glm::vec2 anchorMax = glm::vec2(0, 0);

    float width;
    float height;

    void setLeft(float v);
    void setRight(float v);
    void setTop(float v);
    void setBottom(float v);

    glm::vec3 getPosition() override;
    glm::vec3 getMaxPosition();
    glm::vec2 getDimensions() override;
    glm::mat4 getTranslationMatrix() override;
    glm::mat4 getModelMatrix() override;

private:
    glm::vec2 getParentDimensions();
    glm::vec3 getParentPosition();
};