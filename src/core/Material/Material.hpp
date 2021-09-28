#pragma once

#include <GL/glew.h>
#include <string>

class Material {
public:
    GLuint shaderProgramId;

    Material(char* vertexShaderPath, char* fragmentShaderPath);
    
    void setFloat();
    void setInt();

    void setVec3();
    void setVec4();
private:

};
