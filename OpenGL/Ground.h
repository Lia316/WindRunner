#pragma once
#include "Entity.h"

class Ground : public Entity {
protected:

public:
	Ground();
	Ground(float height);
	void draw();
	void move();
};