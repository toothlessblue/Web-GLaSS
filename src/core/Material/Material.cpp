#include <GL/glew.h>

#include "Material.hpp"
#include "../Shaders/Shaders.hpp"
#include "../../../include/glm/glm.hpp"

Material::Material(char* vertexShaderPath, char* fragmentShaderPath)
{
    this->shaderProgramId = Shaders::CreateProgram(vertexShaderPath, fragmentShaderPath);
}

void Material::setFloat(char* name, float* value) {
    GLint index = glGetAttribLocation(this->shaderProgramId, name);
    // TODO 
}

void Material::setInt(char* name, int* value) {
    GLint index = glGetAttribLocation(this->shaderProgramId, name);
    // TODO 
}

void Material::setVec3(char* name, glm::vec3* value) {
    GLint index = glGetAttribLocation(this->shaderProgramId, name);
    // TODO 
}

void Material::setVec4(char* name, glm::vec4* value) {
    GLint index = glGetAttribLocation(this->shaderProgramId, name);
    // TODO 
}
