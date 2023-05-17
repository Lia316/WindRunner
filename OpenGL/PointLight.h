#pragma once
#include "Entity.h"

class PointLight : public Entity {
protected:

public:
	PointLight(float x, float y, Model* model, GLuint shaderProgram);
	~PointLight() {};
	const type_info& getType() override { return typeid(PointLight); }

	void draw();
};