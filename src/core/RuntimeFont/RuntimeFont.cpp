#include "RuntimeFont.hpp"

namespace RuntimeFont {
    FT_Library freeTypeLibrary;
    std::map<char*, FontFace, cmp_str> faceCache;

    void init() {
        if (FT_Init_FreeType(&freeTypeLibrary))
        {
            std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        }
    }

    FontFace loadFont(char* filepath) {
        if (!RuntimeFont::faceCache.count(filepath)) {
            FT_Face face;
            
            FontFace fontFace = {
                filepath,
                NULL,
                std::map<char, Character>(),
                48, // Font size
                false,
            };

            fontFace.load();

            RuntimeFont::faceCache.insert(std::pair<char*, FontFace>(filepath, fontFace));
        }

        return faceCache[filepath];
    }

    void FontFace::load() {
        this->loaded = true;
        if (FT_New_Face(RuntimeFont::freeTypeLibrary, this->filepath, 0, &this->face))
        {
            std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        }
    }

    void FontFace::clearResources() {
        FT_Done_Face(this->face);
        this->loaded = true;
    }

    void FontFace::cacheManyCharacters(unsigned char range) {
        for (unsigned char c = 0; c < range; c++) {
            this->loadCharacter(c);
        }
    }

    Character FontFace::loadCharacter(char c) {
        if (!this->characters.count(c)) {
            if (!this->loaded) { // need to reload in order to load uncached character
                std::cout << "Reloading cleared FontFace" << std::endl;
                this->load();
                this->loaded = false;
            }

            glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 

            FT_Set_Pixel_Sizes(this->face, 0, this->fontSize);
            if (FT_Load_Char(this->face, c, FT_LOAD_RENDER)) {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            }

            // generate texture
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);

            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                this->face->glyph->bitmap.width,
                this->face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                this->face->glyph->bitmap.buffer
            );

            // set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            Character character = {
                texture, 
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                face->glyph->advance.x
            };

            this->characters.insert(std::pair<char, Character>(c, character));

            glBindTexture(GL_TEXTURE_2D, 0);
        }

        return this->characters[c];
    }
};