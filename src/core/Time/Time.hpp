#include <chrono>

namespace Time {
    extern std::chrono::steady_clock::time_point start;
    extern std::chrono::steady_clock::time_point end;

    extern int frameCount;

    void incrementFrameCounter();

    void frameStart();
    void frameEnd();

    float getDeltaTime();
}