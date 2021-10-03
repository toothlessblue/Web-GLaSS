#pragma once
#include <GLFW/glfw3.h>

class Screen {
public:
    int width;
    int height;

    GLFWwindow* window;

    Screen(int width, int height);
    float getRatio();
    float horizontalFieldOfViewDegreesToVerticalRadians(float horizontalFieldOfViewDegrees);
};