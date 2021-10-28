#pragma once

#include <GL/glew.h>
#include <string>
#include <map>
#include <iostream>
#include <list>
#include <functional>
#include <vector>

#include "../../../include/glm/glm.hpp"
#include "../Texture/Texture.hpp"

struct TextureBinding {
    GLuint textureId;
    GLuint textureUnit;
};

class Material {
public:
    GLuint shaderProgramId;

    Material(const char* vertexShaderPath, const char* fragmentShaderPath);
    
    void setFloat(const char* name, float value);
    void setInt(const char* name, int value);

    void setVec3(const char* name, glm::vec3 value);
    void setVec4(const char* name, glm::vec4 value);

    void setMat4(const char* name, glm::mat4 value);

    void setTexture(const char* name, Texture* texture);
    void setTexture(const char* name, GLuint textureId);

    void use();
private:
    std::vector<TextureBinding> textureBindings;

    void executeOnUse(std::function<void()>);
    GLint getAttributeIndex(const char* name);

    GLuint textureUnitCounter = 6;

    std::map<std::string, GLint> attributeIndexCache;
    std::list<std::function<void()>> toExecuteOnUse;
};
