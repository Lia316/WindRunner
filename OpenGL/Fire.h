#pragma once
#include "Entity.h"

class Fire : public Entity {
protected:

public:
	Fire(float x, float y, Model* model);
	~Fire() {};
	const type_info& getType() override { return typeid(Fire); }

	void draw();
};