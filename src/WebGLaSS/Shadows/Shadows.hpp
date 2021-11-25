#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../WebGLaSS.hpp"

namespace Shadows {
    const unsigned int resolution = 1024;
    extern GLuint depthmapFramebuffer;
    extern float nearPlane;
    extern float farPlane;

    void initialise();
}