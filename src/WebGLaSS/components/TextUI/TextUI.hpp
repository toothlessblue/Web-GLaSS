#pragma once
#include "../Renderer2d/Renderer2d.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../../../../include/glm/glm.hpp"
#include "../../RuntimeFont/RuntimeFont.hpp"
#include "../../../../include/ft2build.h"
#include "../../../../include/freetype/freetype.h"
#include "../../Utils/StringUtils.hpp"
#include <iosfwd>

class TextUI : public Renderer2d {
public:
    glm::vec3 colour;
    
    TextUI();

    void setFont(const char* filepath);
    void setFont(RuntimeFont::FontFace* fontFace);
    void render() override;
    void setText(const char* text);
    void setColour(glm::vec3 colour);
    
    RuntimeFont::FontFace* getFont();
private:
    const char* text;
    RuntimeFont::FontFace* face;
    GLuint vbo;
    Mesh textMesh;
};
