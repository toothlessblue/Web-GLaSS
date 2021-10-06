#include <GL/glew.h>
#include <map>
#include <string>
#include <iostream>
#include <functional>

#include "Material.hpp"
#include "../Shaders/Shaders.hpp"
#include "../../../include/glm/glm.hpp"
#include "../Texture/Texture.hpp"

Material::Material(const char* vertexShaderPath, const char* fragmentShaderPath) {
    this->shaderProgramId = Shaders::CreateProgram(vertexShaderPath, fragmentShaderPath);
}

void Material::setFloat(const char* name, float value) {
    GLint index = this->getAttributeIndex(name);

    this->toExecuteOnUse.push_back([index, value] {
        glUniform1f(index, value);
    });
}

void Material::setInt(const char* name, int value) {
    GLint index = this->getAttributeIndex(name);

    this->toExecuteOnUse.push_back([index, value] {
        glUniform1i(index, value);
    });
}

void Material::setVec3(const char* name, glm::vec3 value) {
    GLint index = this->getAttributeIndex(name);

    this->toExecuteOnUse.push_back([index, value] {
        glUniform3fv(index, 1, &value[0]);
    });
}

void Material::setVec4(const char* name, glm::vec4 value) {
    GLint index = this->getAttributeIndex(name);
    
    this->toExecuteOnUse.push_back([index, value] {
        glUniform4fv(index, 1, &value[0]);
    });
}

void Material::setMat4(const char* name, glm::mat4 value) {
    GLint index = this->getAttributeIndex(name);

    this->toExecuteOnUse.push_back([index, value] {
        glUniformMatrix4fv(index, 1, GL_FALSE, &value[0][0]);
    });
}

void Material::setTexture(const char* name, Texture* value) {
    // TODO store and (maybe) dispose of texture here, so that a reference to the pointer is kept

    GLint index = this->getAttributeIndex(name);

    this->toExecuteOnUse.push_back([index, value, this] {
        glUniform1i(index, this->textureUnitCounter);
        glActiveTexture(GL_TEXTURE0 + this->textureUnitCounter);
        glBindTexture(GL_TEXTURE_2D, value->id);

        this->textureUnitCounter++;
    });
}

void Material::use() {
    glUseProgram(this->shaderProgramId);

    for (std::function<void()> call : this->toExecuteOnUse) {
        call();
    }

    this->toExecuteOnUse.clear();
}

GLint Material::getAttributeIndex(const char* name) {
    std::string string(name);
    GLint location;

    if (!this->attributeIndexCache.count(string)) {
        location = glGetUniformLocation(this->shaderProgramId, name);
        this->attributeIndexCache[string] = location;
    } else {
        location = this->attributeIndexCache[string];
    }

    return location;
}