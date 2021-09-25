#include "../Component.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

class Transform : Component {
public:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};