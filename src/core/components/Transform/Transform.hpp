#pragma once

#include "../../Component/Component.hpp"
#include "../../../../include/glm/glm.hpp"
#include "../../../../include/glm/gtc/quaternion.hpp"
#include "../../../../include/glm/gtx/quaternion.hpp"

class Transform : public Component {
public:
	Transform* parent;

	glm::vec3 position;
	glm::quat rotation;
	glm::vec3 scale;

	Transform();

	glm::mat4 getTranslationMatrix();
	glm::mat4 getRotationMatrix();
	glm::mat4 getScaleMatrix();

	glm::mat4 getModelMatrix();

	glm::mat4 getModelViewProjectionMatrix(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

	glm::vec3 getForwards();
	glm::vec3 getLeft();
	glm::vec3 getUp();
};