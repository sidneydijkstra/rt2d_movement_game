
#ifndef MAP_H
#define MAP_H

#include <rt2d/entity.h>

#include "node.h"

class Map : public Entity
{
public:
	Map();
	virtual ~Map();
	virtual void update(float deltaTime);

	// grid vars
	std::vector<Node*> grid;
	std::vector<Node*> collisionGrid;
	std::vector<Node*> normalGrid;
	Point2 gridMaxSize;
	Point2 nodeMaxSize;

	// create grid
	void spawnGrid();

	// A* function
	std::vector<Node*> getPath(Node* start, Node* end);
	int getGridPos(int x, int y);

	// reset A*
	void resetPath();

	// gets on what grid you are
	bool inBuyGrid(Point2 position, int gridId);
	bool inMysteryGrid(Point2 position, int gridId);
	int getGunFromNode(int gunId);
	int gunBuyListSize();

private:
	// level
	int levelmap[400] = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 3, 1, 0, 0, 0, 0, 0, 0, 0, 2, 1,
		1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	};

	// extra A* functions
	std::vector<Node*> getNeighbours(Node* node);
	int getDistance(Node* nodeA, Node* nodeB);

	// gun buy node's
	int gunBuyGrid[4][4] = // grid id | x pos | y pos | gun id
	{
		{ 2,0,0,0 },
		{ 3,0,0,1 },
		{ 4,0,0,2 },
		{ 5,0,0,3 }
	};

};

#endif /* GRID_H */