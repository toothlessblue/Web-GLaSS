#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Renderer/Renderer.hpp"
#include "../../../../include/glm/glm.hpp"
#include "../../RuntimeFont/RuntimeFont.hpp"
#include "../../../../include/ft2build.h"
#include "../../../../include/freetype/freetype.h"
#include "../../StringUtils/StringUtils.hpp"

class TextRenderer3d : public Renderer {
public:
    TextRenderer3d();

    void setFont(const char* filepath);
    void setFont(RuntimeFont::FontFace* fontFace);
    void render() override;
    void setText(const char* text);
    void setColour(glm::vec3 colour);

    glm::vec3 colour;
private:
    const char* text;
    RuntimeFont::FontFace* face;
    GLuint vbo;
    Mesh textMesh;
};
