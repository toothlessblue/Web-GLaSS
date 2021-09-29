#pragma once

#include <GL/glew.h>
#include <string>
#include <map>

#include "../../../include/glm/glm.hpp"

class Material {
public:
    GLuint shaderProgramId;

    Material(char* vertexShaderPath, char* fragmentShaderPath);
    
    void setFloat(char* name, float* value);
    void setInt(char* name, int* value);

    void setVec3(char* name, glm::vec3* value);
    void setVec4(char* name, glm::vec4* value);
private:
    GLint getAttributeIndex(char* name);
    std::map<std::string, GLint> attributeIndexCache;
};
