#pragma once
#include <chrono>
#include <thread>

namespace Time {
    extern std::chrono::system_clock::time_point lastStart;
    extern std::chrono::system_clock::time_point start;
    extern std::chrono::system_clock::time_point end;
    extern float deltaTime; // Real time between each frame start
    extern float frameTime; // Time taken to compute each frame

    extern unsigned int frameCount;

    void incrementFrameCounter();

    void frameStart();
    void frameEnd();
}