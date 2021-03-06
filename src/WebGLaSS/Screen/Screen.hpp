#pragma once
#include <GLFW/glfw3.h>
#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include <math.h>
#include "../../../include/glm/glm.hpp"

class Screen {
public:
    int width;
    int height;

    GLFWwindow* window;

    Screen(int width, int height); // If screen width/height ever changes, need to update lighting shaders
    ~Screen();
    
    float getRatio();
    float horizontalFieldOfViewDegreesToVerticalRadians(float horizontalFieldOfViewDegrees);
    glm::mat4 get2dProjection();
};