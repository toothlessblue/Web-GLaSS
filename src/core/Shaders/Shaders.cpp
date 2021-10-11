#include "Shaders.hpp"

GLint Shaders::Result = GL_FALSE;
int Shaders::InfoLogLength;

GLuint Shaders::LoadShader(const char* filePath, int shaderType) {
    GLuint shaderId = glCreateShader(shaderType);

    // Read the Vertex Shader code from the file
    std::string shaderCode;
    std::ifstream shaderStream(filePath, std::ios::in);
    if (shaderStream.is_open()) {
        std::stringstream sstr;
        sstr << shaderStream.rdbuf();
        shaderCode = sstr.str();
        shaderStream.close();
    }
    else {
        printf("Impossible to open %s", filePath);
        getchar();
        return 0;
    }

    // Compile Vertex Shader
    printf("Compiling shader : %s\n", filePath);
    char const* sourcePointer = shaderCode.c_str();
    glShaderSource(shaderId, 1, &sourcePointer, NULL);
    glCompileShader(shaderId);

    // Check Vertex Shader
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> shaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(shaderId, InfoLogLength, NULL, &shaderErrorMessage[0]);
        printf("%s\n", &shaderErrorMessage[0]);
    }

    return shaderId;
}

GLuint Shaders::CreateProgram(const GLuint vertexShaderID, const GLuint fragmentShaderID) {
    // Link the program
    printf("Linking program");
    GLuint ProgramID = glCreateProgram();

    glAttachShader(ProgramID, vertexShaderID);
    glAttachShader(ProgramID, fragmentShaderID);
    glLinkProgram(ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }

    glDetachShader(ProgramID, vertexShaderID);
    glDetachShader(ProgramID, fragmentShaderID);

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    return ProgramID;
}

GLuint Shaders::CreateProgram(const char* vertex_file_path, const char* fragment_file_path) {
    // Executed for every rendered vertex
    GLuint vertexShaderID = Shaders::LoadShader(vertex_file_path, GL_VERTEX_SHADER);

    // Executed for every sample, for 4x anti aliasing, this means 4 samples per pixel
    GLuint fragmentShaderID = Shaders::LoadShader(fragment_file_path, GL_FRAGMENT_SHADER);

    return Shaders::CreateProgram(vertexShaderID, fragmentShaderID);
}

GLuint Shaders::CreateProgram(const GLuint fragmentShaderID) {
    // Link the program
    printf("Linking program");
    GLuint ProgramID = glCreateProgram();

    glAttachShader(ProgramID, fragmentShaderID);
    glLinkProgram(ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }

    glDetachShader(ProgramID, fragmentShaderID);
    glDeleteShader(fragmentShaderID);

    return ProgramID;
}

GLuint Shaders::CreateProgram(const char* fragment_file_path) {
    GLuint fragmentShaderID = Shaders::LoadShader(fragment_file_path, GL_FRAGMENT_SHADER);

    return Shaders::CreateProgram(fragmentShaderID);
}