#pragma once
#include <glm/glm.hpp>
#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glut.h>
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
public:
	Model(string filename);
	void load(string filename);
	void draw();
};
