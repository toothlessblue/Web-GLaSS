#include "../include/glm/glm.hpp"
#include <GL/glew.h>

enum TextureType {
    DDS,
}

class Texture {
public:
    GLuint id;

    Texture(const char* filepath, TextureType type);

private:
    void loadDDS(const char* filepath);
};
