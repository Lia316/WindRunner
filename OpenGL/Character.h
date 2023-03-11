#pragma once
#include "Entity.h"

class Character : public Entity {
protected:
	float jumpSpeed;
	bool jumpState; // 점프중(true), 정지중(false)
public:
	Character();
	void draw();
	void jump();
	void reshape(float);
	void setjump();
	void sink();
};