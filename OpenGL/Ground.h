#pragma once
#include "Entity.h"

class Ground : public Entity {
protected:

public:
	Ground(float posX, int height, Model* model);
	~Ground() {};
	const type_info& getType() override { return typeid(Ground); }

	void draw();
};