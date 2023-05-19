#include "Fire.h"

Fire::Fire(float x, float y, Model* model, GLuint* shaderProgram)
	: Entity(x, y, 0, -10, model, shaderProgram) {
	loadTexture(textures->getTextures(TEXTYPE::FIRE), 3);
}

void Fire::draw() {
	if (model == nullptr)
		return;

	glColor3f(9.0, 0.0, 0.0);
	Entity::draw();
}
