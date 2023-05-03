#pragma once
#include "Entity.h"

class Mush : public Entity {
protected:

public:
	Mush(Model* model, GLuint shaderProgram);
	~Mush() {};
	const type_info& getType() override { return typeid(Mush); }

	void draw();
	void setY(float y);
	void reverse();
};