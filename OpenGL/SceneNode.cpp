#include "SceneNode.h"

SceneNode::SceneNode(Entity* entity) {
	this->entity = entity;
	children = {};
	translate = vec3(0, 0, 0);
}

SceneNode::~SceneNode() {
	delete entity;
	entity = nullptr;
	for (unsigned int i = 0; i < children.size(); ++i) {
		delete children[i];
		children[i] = nullptr;
	}
}

void SceneNode::addChild(SceneNode* s) {
	children.push_back(s);
}

void SceneNode::deleteChild(SceneNode* node) {
	if (children.empty() || node == nullptr)
		return;
	for (auto it = children.begin(); it != children.end(); ++it) {
		if (*it == node) {
			delete node;
			*it = nullptr;
			node = nullptr;
			children.erase(it);
			break;
		}
	}
}

void SceneNode::draw() {
	if (entity != nullptr) 
		entity->draw();

	for (vector<SceneNode*>::iterator i = children.begin(); i != children.end(); ++i) {
		(*i)->draw();
	}
}


SceneGraph::SceneGraph(GLuint objectProgram, GLuint lightProgram) {
	objectShader = objectProgram;
	lightShader = lightProgram;
	root = new SceneNode(NULL);
	materials = new Materials();
	initialStructure();
}

void SceneGraph::initialStructure() {
	Model* characterPoses[KEY_FRAME_NUM - 1] = { materials->getModel(CHARACTER1), materials->getModel(CHARACTER2), materials->getModel(CHARACTER3) };

	SceneNode* groundGroup = new SceneNode(new Ground(0, 0, NULL, objectShader));
	SceneNode* starGroup = new SceneNode(new Star(0, 0, NULL, objectShader));
	SceneNode* fireGroup = new SceneNode(new Fire(0, 0, NULL, objectShader));
	SceneNode* mushGroup = new SceneNode(new Mush(NULL, objectShader));
	SceneNode* characterGroup = new SceneNode(new Character(NULL, objectShader));
	SceneNode* lightGroup = new SceneNode(new PointLight(0, 0, NULL, lightShader));

	root->addChild(groundGroup);
	root->addChild(starGroup);
	root->addChild(fireGroup);
	root->addChild(mushGroup);
	root->addChild(characterGroup);
	root->addChild(lightGroup);

	characterGroup->addChild(new SceneNode(new Character(characterPoses, objectShader)));
	lightGroup->addChild(new SceneNode(new PointLight(140, 90, materials->getModel(FIRE), lightShader)));

	float groundWidth = materials->getModel(GROUND)->getWidth();

	for (int i = 0; i < 20; i++) {
		Ground* newGround = new Ground(i * groundWidth, 0, materials->getModel(GROUND), objectShader);
		SceneNode* groundNode = new SceneNode(newGround);

		groundGroup->addChild(groundNode);
	}
}

SceneNode* SceneGraph::findGroup(const type_info& type) {
	for (auto i = root->childBegin(); i != root->childEnd(); ++i) {
		if ((*i)->getEntity()->getType() == type) {
			return (*i);
		}
	}
	return nullptr;
}

// return first node of group
SceneNode* SceneGraph::findNode(const type_info& type) {
	SceneNode* group = findGroup(type);
	if (group->isChild())
		return (*group->childBegin());
	else
		return nullptr;
}

Entity* SceneGraph::findNodeEntity(const type_info& type) {
	SceneNode* firstNode = findNode(type);
	if (firstNode == nullptr)
		return nullptr;
	else
		return firstNode->getEntity();
}


void SceneGraph::addChild(SceneNode* parent, SceneNode* node) {
	if (parent == nullptr || node == nullptr)
		return;
	parent->addChild(node);
}
