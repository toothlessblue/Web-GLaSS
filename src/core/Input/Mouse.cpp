#include "Input.hpp"

namespace Input::Mouse {
    bool locked = false;
    float sensitivity = 1.0f;

    glm::vec2 latePosition;
    glm::vec2 earlyPosition;
    glm::vec2 delta;
    glm::vec2 motion;

    void doLoop() {
        earlyPosition = latePosition;
        
        double xPos, yPos;
        glfwGetCursorPos(GameEngine::screen.window, &xPos, &yPos);
        
        latePosition = glm::vec2(xPos, yPos);
        delta = earlyPosition - latePosition;
        motion = delta * sensitivity * Time::deltaTime;
    }

    void lock() {
        // TODO implement call to JS to hide the mouse
    }

    void unlock() {
        // TODO implement call to JS to show the mouse
    }

    glm::quat getMotionRotation() {
        return glm::quat(glm::vec3(0, motion.x, 0)) * glm::quat(glm::vec3(motion.y, 0, 0));
    }
}