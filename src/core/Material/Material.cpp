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

    this->executeOnUse([index, value] {
        glUniform1f(index, value);
    });
}

void Material::setInt(const char* name, int value) {
    GLint index = this->getAttributeIndex(name);

    this->executeOnUse([index, value] {
        glUniform1i(index, value);
    });
}

void Material::setVec3(const char* name, glm::vec3 value) {
    GLint index = this->getAttributeIndex(name);

    this->executeOnUse([index, value] {
        glUniform3fv(index, 1, &value[0]);
    });
}

void Material::setVec4(const char* name, glm::vec4 value) {
    GLint index = this->getAttributeIndex(name);
    
    this->executeOnUse([index, value] {
        glUniform4fv(index, 1, &value[0]);
    });
}

void Material::setMat4(const char* name, glm::mat4 value) {
    GLint index = this->getAttributeIndex(name);

    this->executeOnUse([index, value] {
        glUniformMatrix4fv(index, 1, GL_FALSE, &value[0][0]);
    });
}

void Material::setTexture(const char* name, Texture* value) {
    this->setTexture(name, value->id);
}

void Material::setTexture(const char* name, GLuint textureId) {
    GLint index = this->getAttributeIndex(name);
    GLuint unit = this->textureUnitCounter;

    this->textureBindings.push_back({
        textureId,
        GL_TEXTURE0 + unit
    });
    
    this->executeOnUse([index, unit] {
        glUniform1i(index, unit);
    });

    this->textureUnitCounter++;
}

void Material::executeOnUse(std::function<void()> toExecute) {
    GLint id;
    glGetIntegerv(GL_CURRENT_PROGRAM,&id);

    if (id == this->shaderProgramId) {
        toExecute();
    } else {
        this->toExecuteOnUse.push_back(toExecute);
    }
}

void Material::use() {
    glUseProgram(this->shaderProgramId);

    for (std::function<void()> call : this->toExecuteOnUse) {
        call();
    }

    for (TextureBinding binding : this->textureBindings) {
        glActiveTexture(binding.textureUnit);
        glBindTexture(GL_TEXTURE_2D, binding.textureId);
    }

    this->toExecuteOnUse.clear();
}

GLint Material::getAttributeIndex(const char* name) {
    std::string string(name);

    if (!this->attributeIndexCache.count(string)) {
        this->attributeIndexCache[string] = glGetUniformLocation(this->shaderProgramId, name);
    }

    return this->attributeIndexCache[string];
}