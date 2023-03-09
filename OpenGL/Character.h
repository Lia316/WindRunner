#pragma once
#include "Entity.h"

class Character : public Entity {
protected:

public:
	Character();
	void draw();
	void jump();
};