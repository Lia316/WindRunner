#pragma once
class Entity {
protected:
	float speed;
public:
	Entity(float);
	virtual void draw() = 0;
	virtual void move();
};