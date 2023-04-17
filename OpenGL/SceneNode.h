#pragma once
#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glut.h>
#include <vector>

#include "Entity.h"
#include "Ground.h"
#include "Character.h"
#include "Fire.h"
#include "Star.h"
#include "Mush.h"

class SceneNode {
private:
	Entity* entity;
	vector<SceneNode*> children;
public:
	SceneNode(Entity* entity);
	vec3 translate;
	void addChild(SceneNode* s);
	void deleteChild();
	void draw();
	vector<SceneNode*>::iterator getChildIteratorBegin() { return children.begin(); }
	vector<SceneNode*>::iterator getChildIteratorEnd() { return children.end(); }
};


class SceneGraph {
public:
	SceneGraph();
	SceneNode* root;

	void initialStructure();
	SceneNode* findGroup(const type_info& type);
	SceneNode* findNode(SceneNode* node);
	void addChild(SceneNode* parent, SceneNode* node);
	void draw() { root->draw(); }
};

