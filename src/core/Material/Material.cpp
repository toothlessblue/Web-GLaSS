#include "Material.hpp"
#include "../Shaders/Shaders.hpp"

Material::Material(char* vertexShaderPath, char* fragmentShaderPath)
{
    this->shaderProgramId = Shaders::CreateProgram(vertexShaderPath, fragmentShaderPath);
}


