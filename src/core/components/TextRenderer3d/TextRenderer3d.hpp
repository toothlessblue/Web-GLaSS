#pragma once
#include <GL/glew.h>
#include <ft2build.h>
#include <GLFW/glfw3.h>
#include FT_FREETYPE_H
#include "../Renderer/Renderer.hpp"
#include "../../../../include/glm/glm.hpp"
#include "../../RuntimeFont/RuntimeFont.hpp"

class TextRenderer : public Renderer {
    TextRenderer();

    void setFont(char* filepath);
    void setFont(RuntimeFont::FontFace fontFace);
    void render() override;
    void setText(char* text);

    glm::vec3 colour;
private:
    char* text;
    RuntimeFont::FontFace face;
    GLuint vbo;
    

};

