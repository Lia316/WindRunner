#include "SceneNode.h"

SceneNode::SceneNode(Entity* entity) {
	this->entity = entity;
	children = {};
	translate = vec3(0, 0, 0);
}

SceneNode::~SceneNode() {
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
	materials = new Materials();
	initialStructure();
}

void SceneGraph::initialStructure() {
	SceneNode* groundGroup = new SceneNode(new Ground(0, 0, NULL));
	SceneNode* starGroup = new SceneNode(new Star(0, 0, NULL));
	SceneNode* fireGroup = new SceneNode(new Fire(0, 0, NULL));
	SceneNode* mushGroup = new SceneNode(new Mush(NULL));
	SceneNode* characterGroup = new SceneNode(new Character(NULL));

	root->addChild(groundGroup);
	root->addChild(starGroup);
	root->addChild(fireGroup);
	root->addChild(mushGroup);
	root->addChild(characterGroup);

	Model* characterPoses[KEY_FRAME_NUM - 1] = { materials->getModel(CHARACTER1), materials->getModel(CHARACTER2), materials->getModel(CHARACTER3) };

	findGroup(typeid(Ground))->addChild(new SceneNode(new Ground(0, 0, materials->getModel(GROUND))));
	findGroup(typeid(Character))->addChild(new SceneNode(new Character(characterPoses)));
}

SceneNode* SceneGraph::findGroup(const type_info& type) {
	for (auto i = root->childBegin(); i != root->childEnd(); ++i) {
		if (typeid((*i)) == type)
			return (*i);
	}
	return nullptr;
}

SceneNode* SceneGraph::findNode(const type_info& type) {
	SceneNode* group = findGroup(type);
	return (*group->childBegin());
}

void SceneGraph::addChild(SceneNode* parent, SceneNode* node) {

}
