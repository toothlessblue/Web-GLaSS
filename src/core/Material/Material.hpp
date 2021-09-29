#pragma once

#include <GL/glew.h>
#include <string>
#include <map>

#include "../../../include/glm/glm.hpp"

class Material {
public:
    GLuint shaderProgramId;

    Material(const char* vertexShaderPath, const char* fragmentShaderPath);
    
    void setFloat(const char* name, float value);
    void setInt(const char* name, int value);

    void setVec3(const char* name, glm::vec3 value);
    void setVec4(const char* name, glm::vec4 value);

    void setMat4(const char* name, glm::mat4 value);
private:
    GLint getAttributeIndex(const char* name);
    std::map<std::string, GLint> attributeIndexCache;
};
