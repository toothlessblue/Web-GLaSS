#pragma once
#include "../../../include/glm/glm.hpp"
#include <GL/glew.h>
#include <string>
#include <GLFW/glfw3.h>
#include <iosfwd>

enum TextureType {
    DDS
};

class Texture {
public:
    GLuint id;
    unsigned char* buffer;

    Texture(const char* filepath, TextureType type);
    Texture(GLuint textureId, unsigned char* buffer);

private:
    void loadDDS(const char* filepath);
};

namespace GenericTextures {
    extern Texture* whiteDot;

    void generate();
}