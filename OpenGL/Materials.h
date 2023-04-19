#pragma once
#include "Model.h"

enum FILENAME {
	CHARACTER1 = 1,
	CHARACTER2,
	CHARACTER3,
	GROUND,
	FIRE,
	STAR,
	MUSHROOM
};

class Materials {
private:
	Model* character1;
	Model* character2;
	Model* character3;
	Model* ground;
	Model* fire;
	Model* star;
	Model* mushroom;

public:
	Materials();
	Model* getModel(int FILENAME);
};