#include "Shadows.hpp"

namespace Shadows {
    GLuint depthmapFramebuffer;
    float nearPlane = 1.0f;
    float farPlane = 25.0f;

    void initialise() {
        // generate depth FBO
        glGenFramebuffers(1, &Shadows::depthmapFramebuffer);
    }
}