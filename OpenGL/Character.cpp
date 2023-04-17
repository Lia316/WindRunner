#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glut.h>
#include <algorithm>
#include "math.h"
#include "Character.h"

#define KEY_FRAME_NUM 4

Character::Character(Model* models[KEY_FRAME_NUM - 1])
    : Entity(glutGet(GLUT_WINDOW_WIDTH) / 10, glutGet(GLUT_WINDOW_HEIGHT) / 4, 0, 0, models[0]) {
	jumpSpeed = 14;
    lowjumpSpeed = 10;
	jumpState = false;
	
	copy(models, models + KEY_FRAME_NUM - 1, this->models);
	time = 0;
	currentKeyFrame = 0;
}

void Character::draw() {
	glColor3f(0.9f, 0.9f, 0.8f);
	Entity::draw();
}

void Character::jump() {
	y += speed;
	if(jumpState == true)
		speed = speed - 0.4;
}

void Character::setjump() {
	if (!jumpState) {//점프중이 아닐 때,
		speed = jumpSpeed;
		jumpState = true;
	}
}

void Character::setlowjump() {
    if (!jumpState) {//점프중이 아닐 때,
        speed = lowjumpSpeed;
        jumpState = true;
    }
}

void Character::setfall() {
    jumpState = true;
}

void Character::stop(Entity* ground) {
    speed = 0;
    jumpState = false;
    y = ground->getHeight();
}

void Character::stepMush() {
    speed = 7;
}
void Character::sink() {
	y -= 10;
}

bool Character::isJumping() {
    return this->jumpState;
}

float Character::getPositionX() {
    return x;
}

float Character::getPositionY() {
    return y;
}

void Character::animation(void(*t)(int))
{
	time += 0.1;
	time = fmod(time, keyFrameTimes[KEY_FRAME_NUM - 1]);
	int currentKeyFrame = 0;

	while (time > keyFrameTimes[currentKeyFrame + 1])
	{
		currentKeyFrame++;
		if (currentKeyFrame == KEY_FRAME_NUM) {
			currentKeyFrame--;
			break;
		}
	}
	Entity::model = models[currentKeyFrame];
}
