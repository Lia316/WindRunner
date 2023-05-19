#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Rpc.h>
#pragma comment(lib, "Rpcrt4.lib")
#include <vector>
#include "RgbImage.h"

enum class TEXTYPE {
	CHARACTER = 1,
	GROUND,
	FIRE,
	STAR,
	MUSHROOM
};

class Textures {
private:
	RgbImage* character;
	RgbImage* ground;
	RgbImage* fire;
	RgbImage* star;
	RgbImage* mushroom;
	RgbImage* normal;
	RgbImage* specular;
public:
	Textures();
	std::vector<RgbImage*> getTextures(TEXTYPE type);
};

extern Textures* textures;