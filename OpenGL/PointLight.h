#pragma once
#include "Entity.h"

class PointLight : public Entity {
protected:

public:
	PointLight(float x, float y, Model* model, GLuint shaderProgram);
	~PointLight() {};

	void draw();
};