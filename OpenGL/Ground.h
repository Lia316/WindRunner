#pragma once
#include "Entity.h"

class Ground : Entity {
protected:

public:
	Ground();
	void draw();
	void move();
	void reshape(float w, float h);
};