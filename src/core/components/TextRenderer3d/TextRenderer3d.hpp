#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Renderer/Renderer.hpp"
#include "../../../../include/glm/glm.hpp"
#include "../../RuntimeFont/RuntimeFont.hpp"
#include "../../../../include/ft2build.h"
#include "../../../../include/freetype/freetype.h"

class TextRenderer3d : public Renderer {
public:
    TextRenderer3d();

    void setFont(char* filepath);
    void setFont(RuntimeFont::FontFace fontFace);
    void render() override;
    void setText(char* text);

    glm::vec3 colour;
private:
    char* text;
    RuntimeFont::FontFace face;
    GLuint vbo;
    Mesh textMesh;
};
