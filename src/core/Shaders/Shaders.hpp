#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string.h>
#include <iosfwd>
#include <vector>
#include <sstream>
#include <fstream>

namespace Shaders {
	extern GLint Result;
	extern int InfoLogLength;

	GLuint LoadShader(const char* filePath, int shaderType);
	GLuint CreateProgram(const GLuint vertexShaderID, const GLuint fragmentShaderID);
	GLuint CreateProgram(const char* vertex_file_path, const char* fragment_file_path);
}