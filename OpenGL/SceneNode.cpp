#include "SceneNode.h"

SceneNode::SceneNode(Entity* entity) {
	this->entity = entity;
	children = {};
	translate = vec3(0, 0, 0);
}

SceneNode::~SceneNode(void) {
	delete entity;
	for (unsigned int i = 0; i < children.size(); ++i) {
		delete children[i];
	}
}

void SceneNode::addChild(SceneNode* s) {
	children.push_back(s);
}

void SceneNode::deleteChild() {
	if (!children.empty() && children.front() != nullptr) {
		delete children.front();
		children.erase(children.begin());
	}
}

void SceneNode::draw() {
	glPushMatrix();
	if (entity) entity->draw();
	glTranslatef(translate.x, translate.y, translate.z);
	for (vector<SceneNode*>::iterator i = children.begin(); i != children.end(); ++i) {
		(*i)->draw();
	}
	glPopMatrix();
}


SceneGraph::SceneGraph() {
	root = new SceneNode(NULL);
}

void SceneGraph::initialStructure() {
	SceneNode* groundGroup = new SceneNode(new Ground());
	SceneNode* starGroup = new SceneNode(new Star());
	SceneNode* fireGroup = new SceneNode(new Fire());
	SceneNode* mushGroup = new SceneNode(new Mush());
	SceneNode* characterGroup = new SceneNode(new Character());

	root->addChild(groundGroup);
	root->addChild(starGroup);
	root->addChild(fireGroup);
	root->addChild(mushGroup);
	root->addChild(characterGroup);
}

SceneNode* SceneGraph::findGroup(const type_info& type) {
	for (vector<SceneNode*>::iterator i = root->getChildIteratorBegin(); i != root->getChildIteratorEnd(); ++i) {
		if (typeid((*i)) == type)
			return (*i);
	}
	return nullptr;
}

void SceneGraph::addChild(SceneNode* parent, SceneNode* node) {

}
