#include <string>
#include <GL/glew.h>
#include "Texture.hpp"
#include "../../../include/glm/glm.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

Texture::Texture(const char* filepath, TextureType type) {
    switch (type) {
        case DDS:
            this->loadDDS(filepath);
            break;
    }
}

Texture::Texture(GLuint id, unsigned char* buffer) {
    this->id = id;
    this->buffer = buffer;
}

void Texture::loadDDS(const char* filepath) {
    unsigned char header[124];

    FILE *fp;

    /* try to open the file */
    fp = fopen(filepath, "rb");
    if (fp == NULL) {
        this->id = 0;
        return;
    }

    /* verify the type of file */
    char filecode[4];
    fread(filecode, 1, 4, fp);
    if (strncmp(filecode, "DDS ", 4) != 0) {
        fclose(fp);
        this->id = 0;
        return;
    }

    /* get the surface desc */
    fread(&header, 124, 1, fp); 

    unsigned int height      = *(unsigned int*)&(header[8 ]);
    unsigned int width       = *(unsigned int*)&(header[12]);
    unsigned int linearSize  = *(unsigned int*)&(header[16]);
    unsigned int mipMapCount = *(unsigned int*)&(header[24]);
    unsigned int fourCC      = *(unsigned int*)&(header[80]);

    unsigned int bufsize;
    /* how big is it going to be including all mipmaps? */
    this->buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
    fread(this->buffer, 1, bufsize, fp);
    /* close the file pointer */
    fclose(fp);

    unsigned int components  = (fourCC == FOURCC_DXT1) ? 3 : 4;
    unsigned int format;
    switch(fourCC)
    {
    case FOURCC_DXT1:
        format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
        break;
    case FOURCC_DXT3:
        format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
        break;
    case FOURCC_DXT5:
        format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
        break;
    default:
        free(this->buffer);
        this->id = 0;
        return;
    }

    // Create one OpenGL texture
    glGenTextures(1, &this->id);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, this->id);

    unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
    unsigned int offset = 0;

    /* load the mipmaps */
    for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
    {
        unsigned int size = ((width+3)/4)*((height+3)/4)*blockSize;
        glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height, 
            0, size, this->buffer + offset);

        offset += size;
        width  /= 2;
        height /= 2;
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    free(this->buffer);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture* GenericTextures::whiteDot = NULL;
void GenericTextures::generate() {
    GLuint id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    
    unsigned char pixels[4] = {255, 255, 255, 255};

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixels[0]);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    GenericTextures::whiteDot = new Texture(id, pixels);
}