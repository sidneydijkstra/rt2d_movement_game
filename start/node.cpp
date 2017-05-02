
#include "node.h"

Node::Node() : Entity(){
}

Node::~Node(){}

void Node::update(float deltaTime){}

// set pos on grid
void Node::setGridPos(int x, int y) {
	gridX = x;
	gridY = y;
}

// reset node vars
void Node::reset() {
	gCost = 0;
	hCost = 0;
	fCost = 0;
	parent = NULL;
}

