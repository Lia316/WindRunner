#include "PointLight.h"

PointLight::PointLight(float x, float y, Model* model, GLuint shaderProgram)
	: Entity(x, y, 0, 0, model, shaderProgram) { }

void PointLight::draw() {
	if (model == nullptr)
		return;
	Entity::draw();
}

void PointLight::rotate(vec3 base, float angle) {
	x = base.x + 100 * cos(angle);
	y = base.y + 80;
	z = base.z + 100 * sin(angle);
}

vec3 PointLight::getPosition() {
	return vec3(x, y, z);
}