#pragma once
#include "Entity.h"

class Ground : public Entity {
protected:

public:
	Ground(Model* model);
	//Ground(float height);
	void draw();
};