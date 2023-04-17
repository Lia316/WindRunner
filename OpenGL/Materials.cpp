#include "Materials.h"

Materials::Materials() {
	character1 = new Model("C:/Users/light/source/repos/character_pose1.obj");
	character2 = new Model("C:/Users/light/source/repos/character_pose2.obj");
	character3 = new Model("C:/Users/light/source/repos/character_pose1.obj");
	ground = new Model("C:/Users/light/source/repos/cube.obj");
	fire = new Model("C:/Users/light/source/repos/fireball.obj");
	star = new Model("C:/Users/light/source/repos/star.obj");
	mushroom = new Model("C:/Users/light/source/repos/Mushroom.obj");
}

Model* Materials::getModel(int FILENAME) {
	switch (FILENAME) {
	case CHARACTER1:
		return character1;
	case CHARACTER2:
		return character2;
	case CHARACTER3:
		return character3;
	case GROUND:
		return ground;
	case FIRE:
		return fire;
	case STAR:
		return star;
	case MUSHROOM:
		return mushroom;
	}
}