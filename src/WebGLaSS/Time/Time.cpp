#include "Time.hpp"

std::chrono::system_clock::time_point Time::lastStart;
std::chrono::system_clock::time_point Time::start;
std::chrono::system_clock::time_point Time::end;

float Time::deltaTime;
float Time::frameTime;

unsigned int Time::frameCount = 0;

unsigned int targetFps = 60;
unsigned int targetDeltaTime = 1000 / targetFps;

void Time::incrementFrameCounter() {
    Time::frameCount++;
}

void Time::frameStart() {
    Time::lastStart = Time::start;
    Time::start = std::chrono::system_clock::now();
}

void Time::frameEnd() {
    Time::end = std::chrono::system_clock::now();

    std::chrono::duration<float> frameElapsed = Time::end - Time::start;
    Time::frameTime = frameElapsed.count();

    std::chrono::duration<float> realElapsed = Time::start - Time::lastStart;
    Time::deltaTime = realElapsed.count();

    int timeToWait = targetDeltaTime - Time::frameTime;

    if (timeToWait > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(timeToWait));
    }
}