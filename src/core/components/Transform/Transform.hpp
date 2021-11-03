#pragma once

#include "../../Component/Component.hpp"
#include "../../../../include/glm/glm.hpp"
#include "../../../../include/glm/gtc/quaternion.hpp"
#include "../../../../include/glm/gtx/quaternion.hpp"

class Transform : public Component {
public:
	Transform* parent = NULL;

	glm::vec3 position;
	glm::quat rotation;
	glm::vec3 scale;

	Transform();

	virtual glm::mat4 getTranslationMatrix();
	virtual glm::mat4 getRotationMatrix();
	virtual glm::mat4 getScaleMatrix();

	virtual glm::mat4 getModelMatrix();

	glm::vec3 getForwards();
	glm::vec3 getLeft();
	glm::vec3 getUp();

	virtual glm::vec3 getWorldPosition();

	virtual glm::vec2 getDimensions();
};