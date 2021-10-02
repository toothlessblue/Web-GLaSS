#pragma once
#include "../../../include/glm/glm.hpp"
#include <GL/glew.h>

enum TextureType {
    DDS
};

class Texture {
public:

    GLuint id;
    unsigned char* buffer;

    Texture(const char* filepath, TextureType type);

private:
    void loadDDS(const char* filepath);
};
