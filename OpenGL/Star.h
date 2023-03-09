#pragma once
#include "Entity.h"

class Star : Entity {
protected:
	int point;
public:
	Star();
	void draw();
	int getPoint();
};