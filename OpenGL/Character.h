#pragma once
#include "Entity.h"

#define KEY_FRAME_NUM 5
#define JOINT_NUM 8

class Character : public Entity {

protected:
	float jumpSpeed;
	float lowjumpSpeed;
	bool jumpState; // 점프중(true), 정지중(false)

	// animation
	float upArmAngleL;
	float upArmAngleR;
	float lowArmAngleL;
	float lowArmAngleR;
	float upLegAngleL;
	float upLegAngleR;
	float lowLegAngleL;
	float lowLegAngleR;

	double time;
	int currentKeyFrame;
	const float keyFrameTimes[KEY_FRAME_NUM] = { 0.0f, 1.0f, 2.0f, 3.0f, 4.0f };
	const float keyFrameAngles[KEY_FRAME_NUM][JOINT_NUM] = {
		// upArmL upArmR lowArmL lowArmR upLegL upLegR lowLegL lowLegR
		{-30, 30, 0, 0, 0, -60, 0, 90},
		{-60, 60, -30, -30, 30, -30, 0, 0},
		{30, -30, 0, 0, -60, 0, 90, 0},
		{60, -60, -30, -30, -30, 30, 0, 0},
		{-30, 30, 0, 0, 0, -60, 0, 90}
	};

	void drawHead();
	void drawTorso();
	void drawLeftArm();
	void drawRightArm();
	void drawPelvis();
	void drawLeftLeg();
	void drawRightLeg();
	float* interpolateKeyframes(double&);
	

public:
	Character();
	void draw();
	void jump();
	void setjump();
	void setlowjump();
	void stop(Entity* ground);
	void sink();
	void animation(void(*t)(int));
};