#include "Material.hpp"

// TODO on every set function, check a cache to make sure the value in the shader is not the same, might be faster

Material::Material(const char* vertexShaderPath, const char* fragmentShaderPath) {
    this->shaderProgramId = Shaders::CreateProgram(vertexShaderPath, fragmentShaderPath);
}

void Material::setFloat(const char* name, float value) {
    GLint index = this->getAttributeIndex(name);

    glUseProgram(this->shaderProgramId);
    glUniform1f(index, value);
}

void Material::setInt(const char* name, int value) {
    GLint index = this->getAttributeIndex(name);

    glUseProgram(this->shaderProgramId);
    glUniform1i(index, value);
}

void Material::setVec3(const char* name, glm::vec3 value) {
    GLint index = this->getAttributeIndex(name);

    glUseProgram(this->shaderProgramId);
    glUniform3fv(index, 1, &value[0]);
}

void Material::setVec4(const char* name, glm::vec4 value) {
    GLint index = this->getAttributeIndex(name);
    
    glUseProgram(this->shaderProgramId);
    glUniform4fv(index, 1, &value[0]);
}

void Material::setMat4(const char* name, glm::mat4 value) {
    GLint index = this->getAttributeIndex(name);

    glUseProgram(this->shaderProgramId);
    glUniformMatrix4fv(index, 1, GL_FALSE, &value[0][0]);
}

void Material::setTexture(const char* name, Texture* value) {
    this->setTexture(name, value->id);
}

void Material::setTexture(const char* name, GLuint textureId) {
    GLint index = this->getAttributeIndex(name);

    this->textureBindings.push_back({ // TODO handle texture being replaced
        textureId,
        GL_TEXTURE0 + this->textureUnitCounter
    });
    
    glUseProgram(this->shaderProgramId);
    glUniform1i(index, this->textureUnitCounter);

    this->textureUnitCounter++;
}

void Material::use() {
    glUseProgram(this->shaderProgramId);

    for (TextureBinding binding : this->textureBindings) {
        glActiveTexture(binding.textureUnit);
        glBindTexture(GL_TEXTURE_2D, binding.textureId);
    }
}

void Material::unuse() {
    for (TextureBinding binding : this->textureBindings) {
        glActiveTexture(binding.textureUnit);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    glUseProgram(0);
}

GLint Material::getAttributeIndex(const char* name) {
    std::string string(name);

    if (!this->attributeIndexCache.count(string)) {
        this->attributeIndexCache[string] = glGetUniformLocation(this->shaderProgramId, name);
    }

    return this->attributeIndexCache[string];
}