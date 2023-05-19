#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    string vertexCode;
    string fragmentCode;

    readSource(vertexPath, fragmentPath, vertexCode, fragmentCode);

    const GLchar* vShaderCode = vertexCode.c_str();
    const GLchar* fShaderCode = fragmentCode.c_str();

    GLuint vertex, fragment;

    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    // shader Program
    program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);
    checkCompileErrors(program, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    glUseProgram(program);
}

void Shader::readSource(const char* vertexPath, const char* fragmentPath, string &vertexCode, string &fragCode) {
    ifstream vShaderFile;
    ifstream fShaderFile;

    try {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        stringstream vShaderStream;
        stringstream fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragCode = fShaderStream.str();
    }
    catch (ifstream::failure& e) {
        cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << endl;
    }
}

void Shader::checkCompileErrors(GLuint shader, string type) {
    GLint success;
    GLchar infoLog[1024];

    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << endl;
        }
    }
    else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << endl;
        }
    }
}

void Shader::setBool(const string& name, bool value) const {
    glUniform1i(glGetUniformLocation(program, name.c_str()), (int)value);
}

void Shader::setInt(const string& name, int value) const {
    glUniform1i(glGetUniformLocation(program, name.c_str()), value);
}

void Shader::setFloat(const string& name, float value) const {
    glUniform1f(glGetUniformLocation(program, name.c_str()), value);
}

void Shader::setVec2(const string& name, const glm::vec2& value) const {
    glUniform2fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);
}
void Shader::setVec2(const string& name, float x, float y) const {
    glUniform2f(glGetUniformLocation(program, name.c_str()), x, y);
}

void Shader::setVec3(const string& name, const glm::vec3& value) const {
    glUniform3fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);
}
void Shader::setVec3(const string& name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(program, name.c_str()), x, y, z);
}

void Shader::setVec4(const string& name, const glm::vec4& value) const {
    glUniform4fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);
}
void Shader::setVec4(const string& name, float x, float y, float z, float w) const {
    glUniform4f(glGetUniformLocation(program, name.c_str()), x, y, z, w);
}

void Shader::setMat4(const string& name, const glm::mat4& mat) const {
    glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}