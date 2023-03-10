#pragma once
class Entity {
protected:
	float x, y;
	float width, height;
	float speed;
public:
	Entity(float, float, float, float, float);
	virtual void draw();
	virtual void move();
};