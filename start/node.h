
#ifndef NODE_H
#define NODE_H

#include <rt2d/entity.h>

class Node : public Entity
{
public:

	Node();
	virtual ~Node();
	virtual void update(float deltaTime);

	bool canWalk;
	int gridX, gridY;
	int gCost, hCost, fCost;
	Node* parent;

	void setGridPos(int x, int y);
	void reset();

private:
};

#endif
