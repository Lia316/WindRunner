#pragma once
#include "Model.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Rpc.h>
#pragma comment(lib, "Rpcrt4.lib")

class Entity {
protected:
	UUID uuid;
	GLuint shaderProgram;
	Model* model;
	int filesize;
	GLuint textureIds[5];

	float x, y, z;
	float width, height, depth;
	float speed;

public:
	Entity(float, float, float, float, Model*, GLuint);
	virtual ~Entity();

	virtual const type_info& getType() { return typeid(Entity); }
	const UUID& getUuid() const { return uuid; }

	bool operator==(const Entity& R) const {
		RPC_STATUS s;
		UUID uuid1 = getUuid();
		UUID uuid2 = R.getUuid();
		return UuidCompare(&uuid1, &uuid2, &s) == 0;
	}

	virtual void loadTexture(const char** filename, unsigned int filesize);
	virtual void draw();
	virtual void move();
	virtual float getPositionX();	
	virtual float getPositionY();
	virtual float getPositionZ();
	virtual float getWidth();
	virtual float getHeight();
	virtual float getDepth();
	virtual float getSpeed();
};