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

    FontFace::FontFace(char* filepath, int fontSize) {
        this->filepath = filepath;
        this->fontSize = fontSize;
    }

    FontFace::FontFace() {}

    FontFace loadFont(char* filepath) {
        if (!RuntimeFont::faceCache.count(filepath)) {
            FontFace fontFace(filepath, 48);

            fontFace.load();
            fontFace.generateFontAtlas();
            fontFace.clearResources();

            RuntimeFont::faceCache.insert(std::pair<char*, FontFace>(filepath, fontFace));
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

        FT_GlyphSlot glyph = this->face->glyph;
        this->atlasWidth = 0;
        this->atlasHeight = 0;

        for(int i = glyphStartIndex; i < glyphEndIndex; i++) {
            if(FT_Load_Char(this->face, i, FT_LOAD_RENDER)) {
                fprintf(stderr, "Loading character %c failed!\n", i);
                continue;
            }

            this->atlasWidth += glyph->bitmap.width;
            this->atlasHeight = std::max(this->atlasHeight, glyph->bitmap.rows);
        }

        glActiveTexture(GL_TEXTURE0);
        glGenTextures(1, &this->atlasTexture);
        glBindTexture(GL_TEXTURE_2D, this->atlasTexture);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, this->atlasWidth, this->atlasHeight, 0, GL_RED, GL_UNSIGNED_BYTE, 0);

        int x = 0;
        for(int i = glyphStartIndex; i < glyphEndIndex; i++) {
            if(FT_Load_Char(face, i, FT_LOAD_RENDER))
                continue;

            glTexSubImage2D(GL_TEXTURE_2D, 0, x, 0, glyph->bitmap.width, glyph->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, glyph->bitmap.buffer);

            x += glyph->bitmap.width;

           this->atlasInfo[i].ax = glyph->advance.x >> 6;
           this->atlasInfo[i].ay = glyph->advance.y >> 6;

           this->atlasInfo[i].bw = glyph->bitmap.width;
           this->atlasInfo[i].bh = glyph->bitmap.rows;

           this->atlasInfo[i].bl = glyph->bitmap_left;
           this->atlasInfo[i].bt = glyph->bitmap_top;

           this->atlasInfo[i].tx = (float)x / this->atlasWidth;
        }

        std::cout << "Generated atlas" << std::endl;
    }

    Mesh FontFace::generateMesh(const char *text, float sx, float sy) {
        std::vector<glm::vec3> verts;
        std::vector<glm::vec2> uvs;
        std::vector<unsigned int> triangles;

        int n = 0;

        float x = 0;
        float y = 0;

        int tris = 0;
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

            verts.push_back(glm::vec3(x2    , -y2    , 0));
            verts.push_back(glm::vec3(x2 + w, -y2    , 0));
            verts.push_back(glm::vec3(x2    , -y2 - h, 0));
            verts.push_back(glm::vec3(x2 + w, -y2 - h, 0));

            uvs.push_back(glm::vec2(this->atlasInfo[*character].tx, 0));
            uvs.push_back(glm::vec2(this->atlasInfo[*character].tx + this->atlasInfo[*character].bw / this->atlasWidth, 0));
            uvs.push_back(glm::vec2(this->atlasInfo[*character].tx, this->atlasInfo[*character].bh / this->atlasHeight));
            uvs.push_back(glm::vec2(this->atlasInfo[*character].tx + this->atlasInfo[*character].bw / this->atlasWidth, this->atlasInfo[*character].bh / this->atlasHeight));

            triangles.push_back(tris);
            triangles.push_back(tris + 2);
            triangles.push_back(tris + 1);
            triangles.push_back(tris + 2);
            triangles.push_back(tris + 3);
            triangles.push_back(tris + 1);

            //coords.push_back(glm::vec4(x2, -y2, this->atlasInfo[*character].tx, 0));
            //coords.push_back(glm::vec4(x2 + w, -y2, this->atlasInfo[*character].tx + this->atlasInfo[*character].bw / this->atlasWidth, 0));
            //coords.push_back(glm::vec4(x2, -y2 - h, this->atlasInfo[*character].tx, this->atlasInfo[*character].bh / this->atlasHeight)); //remember: each glyph occupies a different amount of vertical space
            //coords.push_back(glm::vec4(x2 + w, -y2, this->atlasInfo[*character].tx + this->atlasInfo[*character].bw / this->atlasWidth, 0));
            //coords.push_back(glm::vec4(x2, -y2 - h, this->atlasInfo[*character].tx, this->atlasInfo[*character].bh / this->atlasHeight));
            //coords.push_back(glm::vec4(x2 + w, -y2 - h, this->atlasInfo[*character].tx + this->atlasInfo[*character].bw / this->atlasWidth, this->atlasInfo[*character].bh / this->atlasHeight));
        }

        Mesh mesh;

        mesh.setVertices(verts);
        mesh.setUVs(uvs);
        mesh.setIndexes(triangles);
        // Text usually doesn't use normals

        return mesh;
    }
};