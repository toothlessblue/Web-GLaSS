#pragma once
#include "../../../include/glm/glm.hpp"
#include "../Screen/Screen.hpp"

namespace Input {
    namespace Mouse {
        extern float sensitivity;
        extern bool locked;

        void doLoop();

        void lock(); // Hides the mouse and locks it to the center of the screen
        void unlock(); // inverse of lock
        void toggleLock();

        glm::quat getMotionRotation();

        extern glm::vec2 latePosition;  // Most up to date position
        extern glm::vec2 earlyPosition; // Last position
        extern glm::vec2 delta;         // delta between late and early positions
        extern glm::vec2 motion;        // delta multiplied by sensitivity
    }

    namespace Keyboard {
        bool getKey();
    }
}
