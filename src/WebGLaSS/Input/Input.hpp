#pragma once
#include "../../../include/glm/glm.hpp"
#include "../../../include/glm/gtc/quaternion.hpp"
#include "../../../include/glm/gtx/quaternion.hpp"
#include <GLFW/glfw3.h>
#include <emscripten.h>
#include "../WebGLaSS.hpp"
#include "../Screen/Screen.hpp"
#include "../Time/Time.hpp"

namespace Input {
    namespace Mouse {
        extern float sensitivity;
        extern bool locked;

        extern glm::vec2 latePosition;  // Most up to date position
        extern glm::vec2 earlyPosition; // Last position
        extern glm::vec2 delta;         // delta between late and early positions
        extern glm::vec2 motion;        // delta multiplied by sensitivity

        void doLoop();

        void lock(); // Hides the mouse and locks it to the center of the screen
        void unlock(); // inverse of lock

        glm::quat getMotionRotation();
    }

    namespace Keyboard {
        bool getKey(int key);
        glm::vec3 get6KeyVector3d(int forward, int back, int left, int right, int down, int up);
    }
}
