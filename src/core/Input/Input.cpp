#include "Input.hpp"
#include "../../include/glm/glm.hpp"
#include <GLFW/glfw3.h>
#include "../GameEngine/GameEngine.hpp"
#include <emscripten.h>

Input::Mouse::Mouse(float sensitivity) {
    this->sensitivity = sensitivity;
}

void Input::Mouse::doLoop() {
    this->earlyPosition = this->latePosition;
    
    double xPos, yPos;
    glfwGetCursorPos(GameEngine::screen.window, &xPos, &yPos);
    
    this->latePosition = glm::vec2(xPos, yPos);
    this->delta = this->latePosition - this->earlyPosition;
    this->motion = this->delta * this->sensitivity;

    if (this->locked) {
        // Reset cursor to center of the screen
        glfwSetCursorPos(GameEngine::screen.window, GameEngine::screen.width / 2, GameEngine::screen.height / 2);
    }
}

void Input::Mouse::lock() {
    this->locked = true;
    
    // TODO implement call to JS to hide the mouse
}

void Input::Mouse::unlock() {
    this->locked = false;
    
    // TODO implement call to JS to show the mouse
}

void Input::Mouse::toggleLock() {
    this->locked ? this->unlock() : this->lock();
}