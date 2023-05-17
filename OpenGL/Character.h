#pragma once
#include "Entity.h"

#define KEY_FRAME_NUM 4

class Character : public Entity {

protected:
	float jumpSpeed;
	float lowjumpSpeed;
	bool jumpState; // 점프중(true), 정지중(false)

	Model* models[KEY_FRAME_NUM - 1];
	double time;
	int currentKeyFrame;
	const float keyFrameTimes[KEY_FRAME_NUM] = { 0.0f, 1.0f, 2.0f, 3.0f };

public:
	Character(Model* models[KEY_FRAME_NUM - 1], GLuint shaderProgram);
	~Character();
	const type_info& getType() override { return typeid(Character); }

	void draw();
	void jump();
	void setjump();
	void setlowjump();
	void setfall();
	void stop(float groundHeight);
	void sink();
	void stepMush();

	bool isJumping();
	float getPositionX();
	float getPositionY();
	vec3 getPosition();
	void animation(void(*t)(int));
};