#include "Time.hpp"

std::chrono::steady_clock::time_point Time::lastStart;
std::chrono::steady_clock::time_point Time::start;
std::chrono::steady_clock::time_point Time::end;

float Time::deltaTime;
float Time::frameTime;

unsigned int Time::frameCount = 0;

void Time::incrementFrameCounter() {
    Time::frameCount++;
}

void Time::frameStart() {
    Time::lastStart = Time::start;
    Time::start = std::chrono::high_resolution_clock::now();
}

void Time::frameEnd() {
    Time::end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<float> frameElapsed = Time::end - Time::start;
    Time::frameTime = frameElapsed.count();

    std::chrono::duration<float> realElapsed = Time::start - Time::lastStart;
    Time::deltaTime = realElapsed.count();
}