#pragma once
#include "../../../include/glm/glm.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <ft2build.h>
#include <iostream>
#include <map>
#include <math.h>
#include <vector>
#include FT_FREETYPE_H

struct cmp_str
{
   bool operator()(char const *a, char const *b) const
   {
      return std::strcmp(a, b) < 0;
   }
};

namespace RuntimeFont {
    struct AtlasCharacterPositionInfo {
        float ax; // advance.x
        float ay; // advance.y

        float bw; // bitmap.width;
        float bh; // bitmap.rows;

        float bl; // bitmap_left;
        float bt; // bitmap_top;

        float tx; // x offset of glyph in texture coordinates
    };

    class FontFace {
    public:
        FontFace(char* filepath, int fontSize);

        GLuint atlasTexture;
        AtlasCharacterPositionInfo atlasInfo[128];

        unsigned int atlasWidth;
        unsigned int atlasHeight;

        void clearResources();
        void load();
        void generateFontAtlas(unsigned int glyphStartIndex, unsigned int glyphEndIndex);
        void renderText(const char *text, float x, float y, float sx, float sy);

    private:
        char* filepath;
        FT_Face face;
        int fontSize;
        bool loaded = false;
    };

    extern FT_Library freeTypeLibrary;
    extern std::map<char*, FontFace, cmp_str> faceCache;

    void init();

    FontFace loadFont(char* filepath);
}