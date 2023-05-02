#pragma once
#include <windows.h> 
#include <GL/glew.h>
#include <gl/gl.h> 
#include <gl/glut.h>
#include <glm/glm.hpp>

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
	float scale;

	void createMesh();

public:
	Model(string filename);
	~Model();

	GLuint vao;
	GLuint vbo;

	void load(string filename);
	GLuint createMesh(const vector<vec3>& vertices, const vector<vec2>& uvs, const vector<vec3>& normals);
	void draw();

	float getmaxX() const { return maxX * scale; }
	float getmaxY() const { return maxY * scale; }
	float getmaxZ() const { return maxZ * scale; }
	float getminX() const { return minX * scale; }
	float getminY() const { return minY * scale; }
	float getminZ() const { return minZ * scale; }
	float getWidth() const { return width * scale; }
	float getHeight() const { return height * scale; }
	float getDepth() const { return depth * scale; }
};
