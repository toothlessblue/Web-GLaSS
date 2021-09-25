#pragma once

#include "../../Component/Component.hpp"
#include "../../../../include/glm/glm.hpp"

class Transform : public Component {
public:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	Transform();
};