#include "Entity.h"

Entity::Entity(float x, float y, float z, float speed, Model* model, GLuint shaderProgram)
: x(x), y(y), z(z), speed(speed), model(model), shaderProgram(shaderProgram) {
	UuidCreate(&uuid);
	if (model == nullptr) return;

	this->z = model->getminZ() + z;
	width = model->getWidth();
	height = model->getHeight();
	depth = model->getDepth();
}

Entity::~Entity() {
	model = nullptr;
}

void Entity::move() {
	x += speed;
}

void Entity::draw() {
	if (model == nullptr) return;

	mat4 adjust = model->adjustMatrix();
	mat4 move = translate(mat4(1.0f), vec3(x, y, 0));
	mat4 modelMatrix = move * adjust;

	GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &modelMatrix[0][0]);

	model->draw();
}

float Entity::getPositionX() {
	return x;
}

float Entity::getPositionY() {
	return y;
}

float Entity::getPositionZ() {
	return z;
}

float Entity::getWidth() {
	return width;
}

float Entity::getHeight() {
	return height;
}

float Entity::getDepth() {
	return depth;
}

float Entity::getSpeed() {
	return speed;
}