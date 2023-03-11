#pragma once
#include "Entity.h"

class Hole : Entity {
protected:

public:
	Hole();
	void draw();
	void move();
	void reshape(float);
};