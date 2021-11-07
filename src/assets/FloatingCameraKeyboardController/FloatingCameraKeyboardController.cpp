#include "FloatingCameraKeyboardController.hpp"

FloatingCameraKeyboardController::FloatingCameraKeyboardController() {

}

void FloatingCameraKeyboardController::update() {
    glm::vec3 movementVector = Input::Keyboard::get6KeyVector3d(GLFW_KEY_W, GLFW_KEY_S, GLFW_KEY_A, GLFW_KEY_D, GLFW_KEY_Q, GLFW_KEY_E);

    if (abs(glm::length(movementVector)) < 0.7f) return;

    glm::vec3 motionVector = glm::rotate(glm::inverse(this->gameObject->transform->rotation), glm::normalize(movementVector)) * Time::deltaTime * 50.0f;
    this->gameObject->transform->setPosition(this->gameObject->transform->getPosition() + motionVector);
}