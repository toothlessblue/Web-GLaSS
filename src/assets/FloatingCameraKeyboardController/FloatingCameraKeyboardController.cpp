#include "FloatingCameraKeyboardController.hpp"

FloatingCameraKeyboardController::FloatingCameraKeyboardController() {

}

void FloatingCameraKeyboardController::update() {
    glm::vec3 movementVector = Input::Keyboard::get4KeyVector3d(GLFW_KEY_W, GLFW_KEY_S, GLFW_KEY_A, GLFW_KEY_D);

    if (abs(glm::length(movementVector)) < 1) return;

    glm::vec3 motionVector = glm::rotate(glm::inverse(this->gameObject->transform->rotation), movementVector * Time::getDeltaTime());
    this->gameObject->transform->position += motionVector;
}