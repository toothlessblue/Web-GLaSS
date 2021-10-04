#include "../../Input/Input.hpp"
#include "CameraMouseController.hpp"
#include "../../../../include/glm/glm.hpp"
#include "../../../../include/glm/gtc/quaternion.hpp"
#include "../../../../include/glm/gtx/quaternion.hpp"
#include "../../Time/Time.hpp"

void CameraMouseController::update() {
    this->lookVector.x -= Input::Mouse::motion.x;
    this->lookVector.y -= Input::Mouse::motion.y;

    //FPS camera:  RotationX(pitch) * RotationY(yaw)
    glm::quat qPitch = glm::angleAxis(this->lookVector.y, glm::vec3(1, 0, 0));
    glm::quat qYaw = glm::angleAxis(this->lookVector.x, glm::vec3(0, 1, 0));

    glm::quat orientation = glm::normalize(qPitch * qYaw);
    this->gameObject->transform->rotation = glm::toMat4(orientation);
}