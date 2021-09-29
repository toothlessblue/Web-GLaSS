#include <GL/glew.h>
#include <map>
#include <string>

#include "Material.hpp"
#include "../Shaders/Shaders.hpp"
#include "../../../include/glm/glm.hpp"

Material::Material(const char* vertexShaderPath, const char* fragmentShaderPath) {
    this->shaderProgramId = Shaders::CreateProgram(vertexShaderPath, fragmentShaderPath);
}

void Material::setFloat(const char* name, float value) {
    GLint index = this->getAttributeIndex(name);
    glProgramUniform1f(this->shaderProgramId, index, value);
}

void Material::setInt(const char* name, int value) {
    GLint index = this->getAttributeIndex(name);
    glProgramUniform1i(this->shaderProgramId, index, value);
}

void Material::setVec3(const char* name, glm::vec3 value) {
    GLint index = this->getAttributeIndex(name);
    glProgramUniform3f(this->shaderProgramId, index, value.x, value.y, value.z);
}

void Material::setVec4(const char* name, glm::vec4 value) {
    GLint index = this->getAttributeIndex(name);
    glProgramUniform4f(this->shaderProgramId, index, value.x, value.y, value.z, value.w);
}

void Material::setMat4(const char* name, glm::mat4 value) {
    GLint index = this->getAttributeIndex(name);
    glProgramUniformMatrix4fv(this->shaderProgramId, index, 1, GL_FALSE, &value[0][0]);
}

GLint Material::getAttributeIndex(const char* name) {
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