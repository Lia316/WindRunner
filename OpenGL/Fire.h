#pragma once
#include "Entity.h"

class Fire : public Entity {
protected:

public:
	Fire(float x, float y, Model* model);
	void draw();
};