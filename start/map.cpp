
#include "map.h"
#include "math.h"

Map::Map() : Entity(){
	// set grid vars
	gridMaxSize.x = 15;
	gridMaxSize.y = 15;
	nodeMaxSize.x = 100;
	nodeMaxSize.y = 100;

	// set new gun tile
	//gunBuyGrid.push_back(int_); // "id for the grid" | "x pos" | "y pos" | "gun id"

	// spawn the grid
	spawnGrid();
}

Map::~Map() {}

void Map::update(float deltaTime) {} // update

// spawn the grid
void Map::spawnGrid() {
	int currentNode = 0;
	// 2D loop
	for (int y = 0; y < gridMaxSize.y; y++) {
		for (int x = 0; x < gridMaxSize.x; x++) {
			// check node
			if (levelmap[currentNode] == 0) {
				// create node
				Node* node = new Node;
				// add sprite
				node->addSprite("assets/sprite_ground.tga");
				this->addChild(node);
				int xPos = x * nodeMaxSize.x;
				int yPos = y * nodeMaxSize.y;
				node->position = Point2(xPos, yPos);
				node->sprite()->size = Point2(nodeMaxSize.x, nodeMaxSize.y);

				// set A* info
				node->setGridPos(x, y);
				node->canWalk = true;

				// add node to array
				normalGrid.push_back(node);
				grid.push_back(node);
			}
			else if (levelmap[currentNode] == 1) {
				// create node
				Node* node = new Node;
				// add sprite
				node->addSprite("assets/sprite_wall.tga");
				this->addChild(node);
				int xPos = x * nodeMaxSize.x;
				int yPos = y * nodeMaxSize.y;
				node->position = Point2(xPos, yPos);
				node->sprite()->size = Point2(nodeMaxSize.x, nodeMaxSize.y);

				// set A* info
				node->setGridPos(x, y);
				node->canWalk = false;

				// add node to array
				collisionGrid.push_back(node);
				grid.push_back(node);
			}else {

				for (int i = 0; i < sizeof(gunBuyGrid); i++){
					if (gunBuyGrid[i][0] == levelmap[currentNode]) {
						// create node
						Node* node = new Node;
						// add sprite
						node->addSprite("assets/sprite_shop.tga");
						this->addChild(node);
						int xPos = x * nodeMaxSize.x;
						int yPos = y * nodeMaxSize.y;
						node->position = Point2(xPos, yPos);
						node->sprite()->size = Point2(nodeMaxSize.x, nodeMaxSize.y);

						// set A* info
						node->setGridPos(x, y);
						node->canWalk = true;

						// add node to array
						normalGrid.push_back(node);
						grid.push_back(node);

						// set gun buy info
						gunBuyGrid[i][1] = x;
						gunBuyGrid[i][2] = y;

					}
				}

				// add empty node
				//grid.push_back(NULL);
			}

			// next node
			currentNode++;
		}
	}
}


// A* function
std::vector<Node*> Map::getPath(Node* start, Node* end) {
	resetPath();
	// create some arrays
	std::vector<Node*> open;
	std::vector<Node*> closed;

	open.push_back(start);

	while (open.size() > 0) {

		Node* currentNode = NULL;

		// get the node with the least fCost
		float fCost = INFINITY;
		int nodeNum;
		for (int n = 0; n < open.size(); n++) {
			if (open[n]->fCost <= fCost) {
				fCost = open[n]->fCost;
				currentNode = open[n];
				nodeNum = n;
			}
		}

		// remove current node from open and add it to  closed
		open.erase(open.begin() + nodeNum);
		closed.push_back(currentNode);

		// if at end node break
		if (currentNode == end) {
			break;
		}

		// get neighbours of current node
		std::vector<Node*> neighbours = getNeighbours(currentNode);
		for (int n = 0; n < neighbours.size(); n++) {

			// if node in closed or canWalk == false go to next
			if (std::find(closed.begin(), closed.end(), neighbours[n]) != closed.end() || !neighbours[n]->canWalk) {
				continue;
			}

			// if gCost of neighbour is beter set al vars and add to open
			int costToNeighbour = currentNode->gCost + getDistance(currentNode, neighbours[n]);
			if (currentNode->gCost < costToNeighbour || std::find(closed.begin(), closed.end(), neighbours[n]) == closed.end()) {
				neighbours[n]->gCost = costToNeighbour;
				neighbours[n]->hCost = getDistance(neighbours[n], end);
				neighbours[n]->fCost = costToNeighbour + getDistance(neighbours[n], end);
				neighbours[n]->parent = currentNode;

				if (std::find(closed.begin(), closed.end(), neighbours[n]) == closed.end()) {
					open.push_back(neighbours[n]);
				}
			}
		}

	}

	// revers the path an return it
	std::vector<Node*> path;
	Node* currentNode = end;

	while (currentNode != start) {
		path.push_back(currentNode);
		currentNode = currentNode->parent;
	}

	std::reverse(path.begin(), path.end());

	resetPath();
	return path;
}

// reset all the nod vars
void Map::resetPath() {
	for (int i = 0; i < grid.size(); i++){
		grid[i]->reset();
	}
}

// get tile neighbours
std::vector<Node*> Map::getNeighbours(Node* node) {
	std::vector<Node*> neighbours;
	int x = node->gridX;
	int y = node->gridY;

	if (x - 1 != -1) neighbours.push_back(grid[getGridPos(x - 1, y)]);
	if (y - 1 != -1) neighbours.push_back(grid[getGridPos(x, y - 1)]);
	if (x + 1 != gridMaxSize.x) neighbours.push_back(grid[getGridPos(x + 1, y)]);
	if (y + 1 != gridMaxSize.y) neighbours.push_back(grid[getGridPos(x, y + 1)]);

	if (x - 1 != -1 && y - 1 != -1) neighbours.push_back(grid[getGridPos(x - 1, y - 1)]);
	if (x - 1 != -1 && y + 1 != gridMaxSize.y) neighbours.push_back(grid[getGridPos(x - 1, y + 1)]);
	if (x + 1 != gridMaxSize.x && y + 1 != gridMaxSize.y) neighbours.push_back(grid[getGridPos(x + 1, y + 1)]);
	if (x + 1 != gridMaxSize.x && y - 1 != -1) neighbours.push_back(grid[getGridPos(x + 1, y - 1)]);

	return neighbours;
}

// from grid pos to array pos
int Map::getGridPos(int x, int y) {
	return y * gridMaxSize.y + x;
}

// get the distance of the tiles
int Map::getDistance(Node* nodeA, Node* nodeB) {
	int x = nodeA->gridX - nodeB->gridX;
	int y = nodeA->gridY - nodeB->gridY;

	if (x < 0)
		x *= -1;

	if (y < 0)
		y *= -1;

	return 14 * y + 10 * (x - y);
}

// get tile player is on
bool Map::inBuyGrid(Point2 position, int gridId) {
	int x = round(position.x / nodeMaxSize.x);
	int y = round(position.y / nodeMaxSize.y);

	if (gunBuyGrid[gridId][1] == x && gunBuyGrid[gridId][2] == y) {
		return true;
	}else {
		return false;
	}
}

// is player in mystery box
bool Map::inMysteryGrid(Point2 position, int gridId) {
	int x = round(position.x / nodeMaxSize.x);
	int y = round(position.y / nodeMaxSize.y);

	if (gunBuyGrid[gridId][1] == x && gunBuyGrid[gridId][2] == y && gunBuyGrid[gridId][0] == 2) {
		return true;
	}
	else {
		return false;
	}
}

// get weapons from node
int Map::getGunFromNode(int gunId) {
	return gunBuyGrid[gunId][3];
}


// get max weapons in map
int Map::gunBuyListSize() {
	return sizeof(gunBuyGrid);
}
