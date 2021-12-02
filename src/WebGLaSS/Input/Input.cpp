#include "Input.hpp"

bool Input::Keyboard::getKey(int key) {
    return glfwGetKey(WebGLaSS::screen.window, key) == GLFW_PRESS;
}

/**
 * Transforms 3 keys into a WASD like vector that can then be multiplied / rotated to create keyboard controlled movement
 */
glm::vec3 Input::Keyboard::get6KeyVector3d(int forward, int back, int left, int right, int down, int up) {
    glm::vec3 movement(0.0f, 0.0f, 0.0f);
    
    if (getKey(forward)) {
        movement.z -= 1.0f;
    }

    if (getKey(back)) {
        movement.z += 1.0f;
    }

    if (getKey(left)) {
        movement.x -= 1.0f;
    }

    if (getKey(right)) {
        movement.x += 1.0f;
    }
    
    if (getKey(down)) {
        movement.y -= 1.0f;
    }

    if (getKey(up)) {
        movement.y += 1.0f;
    }

    return movement;
}

bool Input::Mouse::locked = false;
float Input::Mouse::sensitivity = 0.1f;

glm::vec2 Input::Mouse::latePosition;
glm::vec2 Input::Mouse::earlyPosition;
glm::vec2 Input::Mouse::delta;
glm::vec2 Input::Mouse::motion;

void Input::Mouse::doLoop() {
    earlyPosition = latePosition;
    
    double xPos, yPos;
    glfwGetCursorPos(WebGLaSS::screen.window, &xPos, &yPos);
    
    latePosition = glm::vec2(xPos, yPos);
    delta = earlyPosition - latePosition;
    motion = delta * sensitivity * Time::deltaTime;
}

void Input::Mouse::lock() {
    // TODO implement call to JS to hide the mouse
}

void Input::Mouse::unlock() {
    // TODO implement call to JS to show the mouse
}

glm::quat Input::Mouse::getMotionRotation() {
    return glm::quat(glm::vec3(0, motion.x, 0)) * glm::quat(glm::vec3(motion.y, 0, 0));
}