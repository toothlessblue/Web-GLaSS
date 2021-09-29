#include "Time.hpp"
#include <chrono>

std::chrono::steady_clock::time_point Time::start;
std::chrono::steady_clock::time_point Time::end;

int Time::frameCount = 0;

void Time::incrementFrameCounter() {
    Time::frameCount++;
}

void Time::frameStart() {
    Time::start = std::chrono::high_resolution_clock::now();
}

void Time::frameEnd() {
    Time::end = std::chrono::high_resolution_clock::now();
}

float Time::getDeltaTime() {
    std::chrono::duration<float> elapsed = Time::end - Time::start;

    return elapsed.count();
}