#include "PointLight.h"

PointLight::PointLight(float x, float y, Model* model, GLuint shaderProgram)
	: Entity(x, y, 0, 10, model, shaderProgram) { }

void PointLight::draw() {
	if (model == nullptr)
		return;
	Entity::draw();
}
