#include <string>
#include <GL/glew.h>
#include "Texture.hpp"
#include "../include/glm/glm.hpp"
#include <GLFW/glfw3.h>
#include <gli/gli.hpp>

Texture::Texture(const char* filepath, TextureType type) {
    switch (type) {
        case DDS:
            this->loadDDS(filepath);
            break;
    }
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

    unsigned char * buffer;
    unsigned int bufsize;
    /* how big is it going to be including all mipmaps? */
    bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
    buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
    fread(buffer, 1, bufsize, fp);
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
        free(buffer);
        this->id = 0;
        return;
    }
}