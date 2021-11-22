#pragma once
#include "../../../../include/glm/glm.hpp"
#include "../../../../include/glm/gtc/quaternion.hpp"
#include "../../../../include/glm/gtx/quaternion.hpp"
#include "../../../../include/glm/gtx/transform.hpp"
#include "../../Component/Component.hpp"
#include "../../Utils/VectorUtils.hpp"

class Transform : public Component {
public:
	Transform();

	virtual glm::vec3 getPosition();
	virtual glm::vec3 getWorldPosition();
	virtual void setPosition(glm::vec3 position);

	virtual void setRoation(glm::quat rotation);
	virtual glm::quat getRotation();

	virtual void addRotation(glm::vec3 rotation);

	glm::vec3 scale = glm::vec3(1,1,1);
	virtual glm::mat4 getTranslationMatrix();
	virtual glm::mat4 getRotationMatrix();
	virtual glm::mat4 getScaleMatrix();
	virtual glm::mat4 getModelMatrix();

	glm::vec3 getForwards();
	glm::vec3 getLeft();
	glm::vec3 getUp();

	virtual glm::vec2 getDimensions();

	Transform* getParent();
	virtual void setParent(Transform* parent);
	std::vector<Transform*> children;

protected:
	Transform* parent = NULL;
	glm::vec3 position = glm::vec3(0,0,0);
	glm::quat rotation;
};