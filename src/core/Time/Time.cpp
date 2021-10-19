#include "Time.hpp"
#include <chrono>

std::chrono::steady_clock::time_point Time::start;
std::chrono::steady_clock::time_point Time::end;
float Time::deltaTime;

int Time::frameCount = 0;

void Time::incrementFrameCounter() {
    Time::frameCount++;
}

void Time::frameStart() {
    Time::start = std::chrono::high_resolution_clock::now();
}

void Time::frameEnd() {
    Time::end = std::chrono::high_resolution_clock::now();
    Time::deltaTime = (Time::end - Time::start).count();
}