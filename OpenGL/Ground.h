#pragma once
#include "Entity.h"

class Ground : public Entity {
protected:

public:
	Ground();
	void draw();
	void move();
};