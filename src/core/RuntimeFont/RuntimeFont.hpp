#pragma once
#include "../../../include/glm/glm.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <map>
#include <math.h>
#include <vector>
#include "../../../include/ft2build.h"
#include "../../../include/freetype/freetype.h"
#include "../Mesh/Mesh.hpp"
#include "../StringUtils/StringUtils.hpp"
#include "../GameEngine/GameEngine.hpp"

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
        FontFace(const char* filepath, int fontSize);
        FontFace();

        GLuint atlasTexture;
        AtlasCharacterPositionInfo atlasInfo[128];

        unsigned int atlasWidth;
        unsigned int atlasHeight;

        void clearResources();
        void load();
        void generateFontAtlas(unsigned int glyphStartIndex = 32, unsigned int glyphEndIndex = 128);
        Mesh generateMesh(const char *text, float ox = 0, float oy = 0);

        const char* filepath;
        bool loaded = false;
        int fontSize;
    private:
        FT_Face face;
    };

    extern FT_Library freeTypeLibrary;
    extern std::map<const char*, FontFace*, StringUtils::cmp_str> faceCache;

    void init();

    FontFace* loadFont(const char* filepath);
}