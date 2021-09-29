#include <GL/glew.h>
#include <map>
#include <string>

#include "Material.hpp"
#include "../Shaders/Shaders.hpp"
#include "../../../include/glm/glm.hpp"

Material::Material(char* vertexShaderPath, char* fragmentShaderPath)
{
    this->shaderProgramId = Shaders::CreateProgram(vertexShaderPath, fragmentShaderPath);
}

void Material::setFloat(char* name, float* value) {
    GLint index = this->getAttributeIndex(name);
    // TODO 
}

void Material::setInt(char* name, int* value) {
    GLint index = this->getAttributeIndex(name);
    // TODO 
}

void Material::setVec3(char* name, glm::vec3* value) {
    GLint index = this->getAttributeIndex(name);
    // TODO 
}

void Material::setVec4(char* name, glm::vec4* value) {
    GLint index = this->getAttributeIndex(name);
    // TODO 
}

GLint Material::getAttributeIndex(char* name) {
    std::string string(name);
    GLint location;

    if (!this->attributeIndexCache.count(string)) {
        location = glGetAttribLocation(this->shaderProgramId, name);
        this->attributeIndexCache[string] = location;
    } else {
        location = this->attributeIndexCache[string];
    }

    return location;
}