#pragma once
#include "Entity.h"

class Ground : public Entity {
protected:

public:
	Ground(float posX, int height, Model* model);
	void draw();
};