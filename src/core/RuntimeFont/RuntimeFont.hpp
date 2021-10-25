#include "../include/glm/glm.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <ft2build.h>
#include <iostream>
#include <map>
#include FT_FREETYPE_H  

struct cmp_str
{
   bool operator()(char const *a, char const *b) const
   {
      return std::strcmp(a, b) < 0;
   }
};

namespace RuntimeFont {
    struct FontFace {
        char* filepath;
        FT_Face face;
        std::map<char, Character> characters;
        int fontSize;
        bool loaded;

        Character loadCharacter(char character);
        void cacheManyCharacters(unsigned char range);
        void clearResources();
        void load();
    };

    struct Character {
        unsigned int TextureID;  // ID handle of the glyph texture
        glm::ivec2   Size;       // Size of glyph
        glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
        unsigned int Advance;    // Offset to advance to next glyph
    };

    extern FT_Library freeTypeLibrary;
    extern std::map<char*, FontFace, cmp_str> faceCache;

    void init();

    FontFace loadFont(char* filepath);
}