#include "RuntimeFont.hpp"
#include <iostream>

namespace RuntimeFont {
    FT_Library freeTypeLibrary;
    std::map<const char*, FontFace*, Utils::String::cmp_str> faceCache;

    void init() {
        if (FT_Init_FreeType(&freeTypeLibrary))
        {
            std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        }
    }

    FontFace::FontFace(const char* filepath, int fontSize) {
        this->filepath = filepath;
        this->fontSize = fontSize;
    }

    FontFace::FontFace() {}

    FontFace* loadFont(const char* filepath) {
        if (!RuntimeFont::faceCache.count(filepath)) {
            FontFace* fontFace = new FontFace(filepath, 48);

            fontFace->load();
            fontFace->generateFontAtlas();
            fontFace->clearResources();

            RuntimeFont::faceCache.insert(std::pair<const char*, FontFace*>(filepath, fontFace));
        }

        return faceCache[filepath];
    }

    void FontFace::load() {
        if (FT_New_Face(RuntimeFont::freeTypeLibrary, this->filepath, 0, &this->face))
        {
            std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
            return;
        }
        
        FT_Set_Pixel_Sizes(this->face, 0, this->fontSize);
        this->loaded = true;
    }

    void FontFace::clearResources() {
        FT_Done_Face(this->face);
        this->loaded = false;
    }

    void FontFace::generateFontAtlas(unsigned int glyphStartIndex, unsigned int glyphEndIndex) {
        std::cout << "Generating atlas for " << this->filepath << std::endl;
        
        // Get combined width of all glyphs, and max height
        const int spacing = 1;

        FT_GlyphSlot glyph = this->face->glyph;
        this->atlasWidth = 0;
        this->atlasHeight = 0;

        for(int i = glyphStartIndex; i < glyphEndIndex; i++) {
            if(FT_Load_Char(this->face, i, FT_LOAD_RENDER)) {
                fprintf(stderr, "Loading character %c failed!\n", i);
                continue;
            }

            this->atlasWidth += glyph->bitmap.width + spacing;
            this->atlasHeight = std::max(this->atlasHeight, glyph->bitmap.rows);
        }

        glGenTextures(1, &this->atlasTexture);
        glBindTexture(GL_TEXTURE_2D, this->atlasTexture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, this->atlasWidth, this->atlasHeight, 0, GL_RED, GL_UNSIGNED_BYTE, 0);

        int x = 0;
        for(int i = glyphStartIndex; i < glyphEndIndex; i++) {
            if(FT_Load_Char(face, i, FT_LOAD_RENDER))
                continue;

            glTexSubImage2D(GL_TEXTURE_2D, 0, x, 0, glyph->bitmap.width, glyph->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, glyph->bitmap.buffer);

            this->atlasInfo[i].ax = glyph->advance.x >> 6;
            this->atlasInfo[i].ay = glyph->advance.y >> 6;
 
            this->atlasInfo[i].bw = glyph->bitmap.width;
            this->atlasInfo[i].bh = glyph->bitmap.rows;
 
            this->atlasInfo[i].bl = glyph->bitmap_left;
            this->atlasInfo[i].bt = glyph->bitmap_top;
 
            this->atlasInfo[i].tx = (float)x / this->atlasWidth;
            
            x += glyph->bitmap.width + spacing;
        }
        
        glBindTexture(GL_TEXTURE_2D, 0);

        std::cout << "Generated atlas" << std::endl;
    }

    Mesh FontFace::generateMesh(const char *text, float ox, float oy) {
        std::vector<glm::vec3> verts;
        std::vector<glm::vec2> uvs;
        std::vector<unsigned int> triangles;

        int n = 0;

        float sx = 1.0f / WebGLaSS::screen.width;
        float sy = 1.0f / WebGLaSS::screen.height;

        float x = 0;
        float y = 0;

        int vCount = 0;
        for (const char *character = text; *character; character++) { 
            float x2 =  x + this->atlasInfo[*character].bl * sx;
            float y2 = -y - this->atlasInfo[*character].bt * sy;
            float w = this->atlasInfo[*character].bw * sx;
            float h = this->atlasInfo[*character].bh * sy;

            /* Advance the cursor to the start of the next character */
            x += this->atlasInfo[*character].ax * sx;
            y += this->atlasInfo[*character].ay * sy;

            /* Skip glyphs that have no pixels */
            if(!w || !h)
                continue;

            verts.push_back(glm::vec3(x2    , -y2    , 0)); // TL
            verts.push_back(glm::vec3(x2 + w, -y2    , 0)); // TR
            verts.push_back(glm::vec3(x2    , -y2 - h, 0)); // BL
            verts.push_back(glm::vec3(x2 + w, -y2 - h, 0)); // BR

            AtlasCharacterPositionInfo c = this->atlasInfo[*character];

            uvs.push_back(glm::vec2(c.tx, 0));
            uvs.push_back(glm::vec2(c.tx + c.bw / this->atlasWidth, 0));
            uvs.push_back(glm::vec2(c.tx,  c.bh / this->atlasHeight));
            uvs.push_back(glm::vec2(c.tx + c.bw / this->atlasWidth, c.bh / this->atlasHeight));

            triangles.push_back(vCount);
            triangles.push_back(vCount + 2);
            triangles.push_back(vCount + 1);

            triangles.push_back(vCount + 2);
            triangles.push_back(vCount + 3);
            triangles.push_back(vCount + 1);

            vCount += 4;
        }

        Mesh mesh;

        mesh.setVertices(verts);
        mesh.setUVs(uvs);
        mesh.setIndexes(triangles);
        mesh.constructVertexBuffer();

        return mesh;
    }
};