#pragma once
#include "Entity.h"

class Character : public Entity {
protected:
	float jumpSpeed;
	bool jumpState; // ������(true), ������(false)
public:
	Character();
	void draw();
	void jump();
	void reshape(float);
	void setjump();
	void sink();
};