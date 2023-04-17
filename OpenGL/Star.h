#pragma once
#include "Entity.h"

class Star : public Entity {
protected:
	int point;
public:
	Star(float x, float y, Model* model);
	void draw();
	int getPoint();
	void upper();
};