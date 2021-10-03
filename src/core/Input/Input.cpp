#include "Input.hpp"
#include "../../../include/glm/glm.hpp"
#include <GLFW/glfw3.h>
#include "../GameEngine/GameEngine.hpp"
#include "../../../include/glm/gtc/quaternion.hpp"
#include "../../../include/glm/gtx/quaternion.hpp"
#include <emscripten.h>

namespace Input {
    namespace Mouse {
        bool locked = false;
        float sensitivity = 0.005f;

        glm::vec2 latePosition;
        glm::vec2 earlyPosition;
        glm::vec2 delta;
        glm::vec2 motion;

        void doLoop() {
            earlyPosition = latePosition;
            
            double xPos, yPos;
            glfwGetCursorPos(GameEngine::screen.window, &xPos, &yPos);
            
            latePosition = glm::vec2(xPos, yPos);
            delta = latePosition - earlyPosition;
            motion = delta * sensitivity;

            if (locked) {
                // Reset cursor to center of the screen
                glfwSetCursorPos(GameEngine::screen.window, GameEngine::screen.width / 2, GameEngine::screen.height / 2);
            }
        }

        void lock() {
            locked = true;
            
            // TODO implement call to JS to hide the mouse
        }

        void unlock() {
            locked = false;
            
            // TODO implement call to JS to show the mouse
        }

        void toggleLock() {
            locked ? unlock() : lock();
        }

        glm::quat getMotionRotation() {
            return glm::quat(glm::vec3(0, motion.x, 0)) * glm::quat(glm::vec3(motion.y, 0, 0));
        }
    }
}