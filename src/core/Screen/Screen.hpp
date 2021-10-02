#pragma once

class Screen {
public:
    int width;
    int height;

    GLFWwindow* window;

    Screen(int width, int height);
    float getRatio();
    float horizontalFieldOfViewDegreesToVerticalRadians(float horizontalFieldOfViewDegrees);
};