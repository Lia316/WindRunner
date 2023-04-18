#pragma once
#include "Entity.h"

class Star : public Entity {
protected:
	int point;
public:
	Star(float x, float y, Model* model);
	~Star() {};
	const type_info& getType() override { return typeid(Star); }

	void draw();
	int getPoint();
	void upper();
};