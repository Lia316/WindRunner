#pragma once
#include "Entity.h"

class Mush : public Entity {
protected:

public:
	Mush();
	void draw();
	void move();
	void setY(float y);
	void reverse();
};