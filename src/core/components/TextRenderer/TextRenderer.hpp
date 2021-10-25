#pragma once
#include <ft2build.h>
#include FT_FREETYPE_H
#include "../../Component/Component.hpp"

class TextRenderer : public Component {
    TextRenderer();

    void setFont(const char* filepath);
    void setFont();
}