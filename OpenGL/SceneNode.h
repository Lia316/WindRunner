#pragma once
#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glut.h>
#include <vector>

#include "Materials.h"
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
	~SceneNode();
	vec3 translate;
	void addChild(SceneNode* s);
	void deleteChild();
	void draw();
	Entity* getEntity() { return entity;  }
	vector<SceneNode*>::iterator childBegin() { return children.begin(); }
	vector<SceneNode*>::iterator childEnd() { return children.end(); }
};


class SceneGraph {
public:
	SceneGraph();
	SceneNode* root;
	Materials* materials;

	void initialStructure();
	SceneNode* findGroup(const type_info& type);
	SceneNode* findNode(const type_info& type);
	void addChild(SceneNode* parent, SceneNode* node);
	void draw() { root->draw(); }
};

