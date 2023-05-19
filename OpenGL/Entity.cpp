#include "Entity.h"
#include "RgbImage.h"

Entity::Entity(float x, float y, float z, float speed, Model* model, GLuint* shaderProgram)
: x(x), y(y), z(z), speed(speed), model(model), shaderProgram(shaderProgram) {
	UuidCreate(&uuid);
	if (model == nullptr) return;

	filesize = 0;

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

void Entity::loadTexture(const char** filename, unsigned int filesize) {
	this->filesize = filesize;

	for (unsigned int i = 0; i < filesize; i++) {
		GLuint texture;

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		RgbImage theTexMap(filename[i]);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, theTexMap.GetNumCols(), theTexMap.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData());
		glGenerateMipmap(GL_TEXTURE_2D);

		textureIds[i] = texture;
	}
}

void Entity::draw() {
	if (model == nullptr) return;

	mat4 adjust = model->adjustMatrix();
	mat4 move = translate(mat4(1.0f), vec3(x, y, 0));
	mat4 modelMatrix = move * adjust;

	GLuint modelLoc = glGetUniformLocation(*shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &modelMatrix[0][0]);

	for (unsigned int i = 0; i < filesize; i++) {
		GLuint textureLoc = glGetUniformLocation(*shaderProgram, textureType[i]);
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textureIds[i]);
		glUniform1i(textureLoc, i);
	}
	if (filesize)
		glActiveTexture(GL_TEXTURE0);

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