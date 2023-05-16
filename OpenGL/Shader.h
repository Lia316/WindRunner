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
    void setBool(const string& name, bool value) const;
    void setInt(const string& name, int value) const;
    void setFloat(const string& name, float value) const;
    void setVec2(const string& name, const glm::vec2& value) const;
    void setVec2(const string& name, float x, float y) const;
    void setVec3(const string& name, const glm::vec3& value) const;
    void setVec3(const string& name, float x, float y, float z) const;
    void setMat4(const string& name, const glm::mat4& mat) const;
private:
    void readSource(const char* vertexPath, const char* fragmentPath, string& vertexCode, string& fragCode);
    void checkCompileErrors(GLuint shader, string type);
};
