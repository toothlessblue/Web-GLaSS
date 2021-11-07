#include "Time.hpp"
#include <chrono>

std::chrono::steady_clock::time_point Time::start;
std::chrono::steady_clock::time_point Time::end;
float Time::deltaTime;

unsigned int Time::frameCount = 0;

void Time::incrementFrameCounter() {
    Time::frameCount++;
}

void Time::frameStart() {
    Time::start = std::chrono::high_resolution_clock::now();
}

void Time::frameEnd() {
    Time::end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<float> elapsed = Time::end - Time::start;
    Time::deltaTime = elapsed.count();
}