#pragma once
#include <GL/glew.h>
#include <gl/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <cstring>
#include "Shader.h"

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

using namespace std;
using namespace glm;

class Text2D {
protected:
    Shader* textShader;
    GLuint loadDDS(const char* imagepath);
    unsigned int Text2DTextureID;
    unsigned int Text2DVertexBufferID;
    unsigned int Text2DUVBufferID;
    unsigned int Text2DShaderID;
    unsigned int Text2DUniformID;
public:
    Text2D(const char* texturePath);
    GLuint getProgramID() { return textShader->program; }
    void printText2D(const char* text, int x, int y, int size);
    void cleanupText2D();
};