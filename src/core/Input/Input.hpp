#include "../../include/glm/glm.hpp"
#include "../Screen/Screen.hpp"

namespace Input {
    class Mouse {
    public:
        float sensitivity;

        Mouse(float sensitivity);

        void doLoop();

        void lock(); // Hides the mouse and locks it to the center of the screen
        void unlock(); // inverse of lock
        void toggleLock();

    private:
        bool locked = false;

        glm::vec2 latePosition;  // Most up to date position
        glm::vec2 earlyPosition; // Last position
        glm::vec2 delta;         // delta between late and early positions
        glm::vec2 motion;        // delta multiplied by sensitivity
    };
}
