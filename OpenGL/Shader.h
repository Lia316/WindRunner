#pragma once
#include <windows.h>
#include <GL/glew.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class Shader {
public:
    GLuint program;
    Shader(const char* vertexPath, const char* fragmentPath);
private:
    void readSource(const char* vertexPath, const char* fragmentPath, string& vertexCode, string& fragCode);
    void checkCompileErrors(GLuint shader, string type);
};
