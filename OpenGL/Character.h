#pragma once
#include "Entity.h"

class Character : public Entity {
protected:
	float jumpSpeed;
public:
	Character();
	void draw();
	void jump();
	void reshape(float);
};