#include "Textures.h"

Textures::Textures() {
	character = new RgbImage("resource/textured_mesh/white.bmp");
	ground = new RgbImage("resource/textured_mesh/cube/BasicShapeMaterial_D.bmp");
	fire = new RgbImage("resource/textured_mesh/fire_ball/M_ContentWindow_D.bmp");
	star = new RgbImage("resource/textured_mesh/orange.bmp");
	mushroom = new RgbImage("resource/textured_mesh/mushroom.bmp");
	normal = new RgbImage("resource/textured_mesh/fire_ball/M_ContentWindow_N.bmp");
	specular = new RgbImage("resource/textured_mesh/fire_ball/M_ContentWindow_S.bmp");
}

std::vector<RgbImage*> Textures::getTextures(TEXTYPE type) {
    switch (type) {
    case TEXTYPE::CHARACTER:
        return { character, normal, specular };
    case TEXTYPE::GROUND:
        return { ground, normal, specular };
    case TEXTYPE::FIRE:
        return { fire, normal, specular };
    case TEXTYPE::STAR:
        return { star, normal, specular };
    case TEXTYPE::MUSHROOM:
        return { mushroom, normal, specular };
    default:
        return {};
    }
}

Textures* textures = new Textures();