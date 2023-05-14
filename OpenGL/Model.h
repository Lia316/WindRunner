#pragma once
#include <windows.h> 
#include <GL/glew.h>
#include <gl/gl.h> 
#include <gl/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;
using namespace glm;

class Model {
protected:
	vector<vec3> verts{};
	vector<vec2> tex_coord{};
	vector<vec3> norms{};
	vector<int> facet_vrt{};
	vector<int> facet_tex{};
	vector<int> facet_nrm{};
	vec3 color;

	float maxX;
	float maxY;
	float maxZ;
	float minX;
	float minY;
	float minZ;
	float avgX;
	float avgY;
	float avgZ;
	float width;
	float height;
	float depth;
	float s;

	void createMesh();

public:
	Model(string filename);
	~Model();

	GLuint vao;
	GLuint vbo;

	void load(string filename);
	void loadTexture(GLuint shaderProgram, const char** filename, unsigned int filesize);
	mat4 adjustMatrix();
	void draw();
	void setColor(vec3);

	float getmaxX() const { return maxX * s; }
	float getmaxY() const { return maxY * s; }
	float getmaxZ() const { return maxZ * s; }
	float getminX() const { return minX * s; }
	float getminY() const { return minY * s; }
	float getminZ() const { return minZ * s; }
	float getWidth() const { return width * s; }
	float getHeight() const { return height * s; }
	float getDepth() const { return depth * s; }
};
