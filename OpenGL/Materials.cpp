#include "Materials.h"

Materials::Materials() {
	character1 = new Model("resource/character_pose1.obj");
	character2 = new Model("resource/character_pose2.obj");
	character3 = new Model("resource/character_pose1.obj");
	ground = new Model("resource/cube.obj");
	fire = new Model("resource/fireball.obj");
	star = new Model("resource/star.obj");
	mushroom = new Model("resource/Mushroom.obj");
}

Model* Materials::getModel(FILENAME filename) {
	switch (filename) {
	case FILENAME::CHARACTER1:
		return character1;
	case FILENAME::CHARACTER2:
		return character2;
	case FILENAME::CHARACTER3:
		return character3;
	case FILENAME::GROUND:
		return ground;
	case FILENAME::FIRE:
		return fire;
	case FILENAME::STAR:
		return star;
	case FILENAME::MUSHROOM:
		return mushroom;
	}
}