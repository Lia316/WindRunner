#pragma once
#include "Entity.h"

class Mush : public Entity {
protected:

public:
	Mush(Model* model);
	void draw();
	void setY(float y);
	void reverse();
};