#pragma once
#include "Model.h"

class Entity {
protected:
	Model* model;
	float x, y, z;
	float width, height, depth;
	float speed;
public:
	Entity(float, float, float, float, Model*);
	virtual void draw();
	virtual void move();
	virtual float getPositionX();	
	virtual float getPositionY();
	virtual float getPositionZ();
	virtual float getWidth();
	virtual float getHeight();
	virtual float getDepth();
	virtual float getSpeed();
};