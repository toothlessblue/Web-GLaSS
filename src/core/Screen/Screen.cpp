#include "Screen.hpp"
#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include <math.h>
#include "../../../include/glm/glm.hpp"

Screen::Screen(int width, int height) {
    this->width = width; 
    this->height = height;

    // Initialise GLFW
    bool glewExperimental = true; // Needed for core profile
    if (!glfwInit())
    {
        throw "Failed to initialize GLFW\n";
    }

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

    // Open a window and create its OpenGL context
    this->window = glfwCreateWindow(this->width, this->height, "Tutorial 01", NULL, NULL);
    if (this->window == NULL) {
        throw "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version.\n";
        glfwTerminate();
    }

    glfwMakeContextCurrent(this->window); // Initialize GLEW
    glewExperimental = true; // Needed in core profile
    if (glewInit() != GLEW_OK) {
        throw "Failed to initialize GLEW\n";
    }
}

float Screen::getRatio() {
    return (float)this->width / (float)this->height;
}

float Screen::horizontalFieldOfViewDegreesToVerticalRadians(float horizontalFieldOfViewDegrees) {
    return glm::radians(2 * atan(tan(horizontalFieldOfViewDegrees / 2) * this->getRatio()));
}