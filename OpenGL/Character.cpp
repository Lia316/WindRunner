#include <algorithm>
#include "math.h"
#include "Character.h"

#define KEY_FRAME_NUM 4

Character::Character(Model* models[KEY_FRAME_NUM - 1], GLuint shaderProgram)
    : Entity(glutGet(GLUT_WINDOW_WIDTH) / 10, glutGet(GLUT_WINDOW_HEIGHT) / 4, 0, 0, NULL, shaderProgram) {
	jumpSpeed = 14;
    lowjumpSpeed = 10;
	jumpState = false;
	
	if (models != nullptr) {
		model = models[0];
		copy(models, models + KEY_FRAME_NUM - 1, this->models);
		width = 20; // can't read model's width height now..
		height = 60;
	}
	time = 0;
	currentKeyFrame = 0;

	const char* file[] = { "C:/Users/light/source/repos/textured_mesh/white.bmp" };
	loadTexture(file, 1);
}

Character::~Character() {
	for (int i = 0; i < KEY_FRAME_NUM - 1; i++) {
		delete models[i];
		models[i] = nullptr;
	}
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

void Character::stop(float groundHeight) {
    speed = 0;
    jumpState = false;
    y = groundHeight;
}

void Character::stepMush() {
    speed = 7;
	jumpState = true;
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
	if (!jumpState)
		Entity::model = models[currentKeyFrame];
	else
		Entity::model = models[0];
}
