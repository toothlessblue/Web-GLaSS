#pragma once
#include "../../../include/glm/glm.hpp"
#include "../../../include/glm/gtc/quaternion.hpp"
#include "../../../include/glm/gtx/quaternion.hpp"
#include <GLFW/glfw3.h>
#include <emscripten.h>
#include "../GameEngine/GameEngine.hpp"
#include "../Screen/Screen.hpp"
#include "../Time/Time.hpp"
#include "../components/Transform/Transform.hpp"

namespace Input {
    namespace Mouse {
        extern float sensitivity;

        void doLoop();

        void lock(); // Hides the mouse and locks it to the center of the screen
        void unlock(); // inverse of lock

        glm::quat getMotionRotation();

        extern glm::vec2 latePosition;  // Most up to date position
        extern glm::vec2 earlyPosition; // Last position
        extern glm::vec2 delta;         // delta between late and early positions
        extern glm::vec2 motion;        // delta multiplied by sensitivity
    }

    namespace Keyboard {
        bool getKey();
        glm::vec3 get4KeyVector3d(int forward, int back, int left, int right);
    }
}
