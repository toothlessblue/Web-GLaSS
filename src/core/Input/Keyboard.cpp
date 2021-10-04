#include "Input.hpp"

namespace Input::Keyboard {
    bool getKey(int key) {
        return glfwGetKey(GameEngine::screen.window, key) == GLFW_PRESS;
    }

    /**
     * Transforms 3 keys into a WASD like vector that can then be multiplied / rotated to create keyboard controlled movement
     */
    glm::vec3 get4KeyVector3d(int forward, int back, int left, int right) {
        glm::vec3 movement;
        
        if (getKey(forward)) {
            movement.z -= 1;
        }

        if (getKey(back)) {
            movement.z += 1;
        }

        if (getKey(left)) {
            movement.x -= 1;
        }

        if (getKey(right)) {
            movement.x += 1;
        }

        return movement;
    }
}