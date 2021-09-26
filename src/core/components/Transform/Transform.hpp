#pragma once

#include "../../Component/Component.hpp"
#include "../../../../include/glm/glm.hpp"

class Transform : public Component {
public:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	Transform();

	glm::mat4 getTranslationMatrix();
	glm::mat4 getRotationMatrix();
	glm::mat4 getScaleMatrix();

	glm::mat4 getModelMatrix();

	glm::mat4 getModelViewProjectionMatrix(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
};