/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2017 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#include <time.h>
#include "scene15.h"

Scene15::Scene15() : SuperScene()
{
	srand((unsigned)time(NULL));

	text[0]->message("Scene15: Conway's Game Of Life. Press [SPACE] to reset. Also try [Q/W/E/S]");

	timer.start();

	// create Canvas
	int pixelsize = 4;
	canvas = new Canvas(pixelsize);
	layers[0]->addChild(canvas);

	// create field
	const int w = canvas->width();
	const int h = canvas->height();
	field = std::vector<bool>(w*h, false);

	this->randomField();
}


Scene15::~Scene15()
{
	layers[0]->removeChild(canvas);
	delete canvas;
}

void Scene15::update(float deltaTime)
{
	// ###############################################################
	// Make SuperScene do what it needs to do (Escape key stops Scene)
	// ###############################################################
	SuperScene::update(deltaTime);

	//text[0]->message(""); // clear title
	//text[1]->message(""); // clear fps message
	text[2]->message(""); // clear [/] next scene
	text[3]->message(""); // clear <esc> to quit
	text[10]->message(""); // clear player click count message

	if (input()->getKeyDown( GLFW_KEY_SPACE )) {
		this->randomField();
	}
	if (input()->getKeyDown( GLFW_KEY_Q )) {
		this->infinitGrowthA();
	}
	if (input()->getKeyDown( GLFW_KEY_E )) {
		this->infinitGrowthB();
	}
	if (input()->getKeyDown( GLFW_KEY_W )) {
		this->rpentomino();
	}
	if (input()->getKeyDown( GLFW_KEY_S )) {
		this->pentadecathlon();
	}

	// ###############################################################
	// Update and draw only when it's time
	// ###############################################################
	float tsec = timer.seconds();
	if (tsec > 0.1 - deltaTime) { // 0.1 is 10 fps
		this->drawField();
		this->gameOfLifeUpdate();

		timer.start();
	}
}

void Scene15::gameOfLifeUpdate()
{
	const int w = canvas->width();
	const int h = canvas->height();
	std::vector<bool> next = std::vector<bool>(w*h, false);

	int counter = 0;
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			int nc = 0; // number of neighbour cells
			Pointi n;

			// check 8 neighbours and count the ones that are alive
			n = this->wrap(Pointi(x-1, y+1)); // top left
			if (field[getIdFromPos(n.x,n.y)] == true) { nc++; }
			n = this->wrap(Pointi(x, y+1)); // top
			if (field[getIdFromPos(n.x,n.y)] == true) { nc++; }
			n = this->wrap(Pointi(x+1, y+1)); // top right
			if (field[getIdFromPos(n.x,n.y)] == true) { nc++; }
			n = this->wrap(Pointi(x-1, y)); // left
			if (field[getIdFromPos(n.x,n.y)] == true) { nc++; }
			n = this->wrap(Pointi(x+1, y)); // right
			if (field[getIdFromPos(n.x,n.y)] == true) { nc++; }
			n = this->wrap(Pointi(x-1, y-1)); // bottom left
			if (field[getIdFromPos(n.x,n.y)] == true) { nc++; }
			n = this->wrap(Pointi(x, y-1)); // bottom
			if (field[getIdFromPos(n.x,n.y)] == true) { nc++; }
			n = this->wrap(Pointi(x+1, y-1)); // bottom right
			if (field[getIdFromPos(n.x,n.y)] == true) { nc++; }

			// Apply rules:
			//- Any live cell with fewer than two live neighbours dies, as if caused by underpopulation.
			//- Any live cell with two or three live neighbours lives on to the next generation.
			//- Any live cell with more than three live neighbours dies, as if by overpopulation.
			//- Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
			bool current = field[getIdFromPos(x,y)];
			if (current == true) { // this cell is alive
				if (nc < 2) { current = false; } // underpopulation
				//if (nc == 2 || nc == 3) { current == true; } // we're happy
				if (nc > 3) { current = false; } // overpopulation
			} else { // this cell is dead
				if (nc == 3) { current = true; } // reproduction
			}

			next[getIdFromPos(x,y)] = current;

			counter++;
		}
	}

	field = next; // this is what we work with now
}

void Scene15::drawField()
{
	const int w = canvas->width();
	const int h = canvas->height();
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			if (field[getIdFromPos(x, y)] == true) {
				canvas->setPixel(x, y, RGBAColor(192,192,192,255));
			} else {
				canvas->setPixel(x, y, BLACK);
			}
		}
	}
}

Pointi Scene15::wrap(Pointi n)
{
	Pointi w = n;

	if (n.x < 0) { w.x = canvas->width()-1; }
	if (n.x > canvas->width()-1) { w.x = 0; }
	if (n.y < 0) { w.y = canvas->height()-1; }
	if (n.y > canvas->height()-1) { w.y = 0; }

	return w;
}

void Scene15::randomField()
{
	const int w = canvas->width();
	const int h = canvas->height();
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			int id = getIdFromPos(x, y);
			if (rand()%2 == 0) {
				field[id] = true;
			} else {
				field[id] = false;
			}
		}
	}
}

void Scene15::infinitGrowthA()
{
	const int w = canvas->width();
	const int h = canvas->height();
	field = std::vector<bool>(w*h, false);

	std::vector<Pointi> points;
	points.push_back(Pointi(1,1));
	points.push_back(Pointi(3,1));
	points.push_back(Pointi(3,2));
	points.push_back(Pointi(5,3));
	points.push_back(Pointi(5,4));
	points.push_back(Pointi(5,5));
	points.push_back(Pointi(7,4));
	points.push_back(Pointi(7,5));
	points.push_back(Pointi(7,6));
	points.push_back(Pointi(8,5));

	size_t s = points.size();
	for (size_t i = 0; i < s; i++) {
		int x = points[i].x;
		int y = points[i].y;
		x += w/2;
		y += h/2;
		field[getIdFromPos(x, y)] = true;
	}
}

void Scene15::infinitGrowthB()
{
	const int w = canvas->width();
	const int h = canvas->height();
	field = std::vector<bool>(w*h, false);

	std::vector<Pointi> points;
	points.push_back(Pointi(1,1));
	points.push_back(Pointi(1,4));
	points.push_back(Pointi(1,5));
	points.push_back(Pointi(2,2));
	points.push_back(Pointi(2,5));
	points.push_back(Pointi(3,1));
	points.push_back(Pointi(3,2));
	points.push_back(Pointi(3,5));
	points.push_back(Pointi(4,3));
	points.push_back(Pointi(5,1));
	points.push_back(Pointi(5,2));
	points.push_back(Pointi(5,3));
	points.push_back(Pointi(5,5));

	size_t s = points.size();
	for (size_t i = 0; i < s; i++) {
		int x = points[i].x;
		int y = points[i].y;
		x += w/2;
		y += h/2;
		field[getIdFromPos(x, y)] = true;
	}
}

void Scene15::rpentomino()
{
	const int w = canvas->width();
	const int h = canvas->height();
	field = std::vector<bool>(w*h, false);

	std::vector<Pointi> points;
	points.push_back(Pointi(1,2));
	points.push_back(Pointi(2,1));
	points.push_back(Pointi(2,2));
	points.push_back(Pointi(2,3));
	points.push_back(Pointi(3,3));

	size_t s = points.size();
	for (size_t i = 0; i < s; i++) {
		int x = points[i].x;
		int y = points[i].y;
		x += w/2;
		y += h/2;
		field[getIdFromPos(x, y)] = true;
	}
}

void Scene15::pentadecathlon()
{
	const int w = canvas->width();
	const int h = canvas->height();
	field = std::vector<bool>(w*h, false);

	std::vector<Pointi> points;
	points.push_back(Pointi(1,0));
	points.push_back(Pointi(1,1));
		points.push_back(Pointi(0,2));
		points.push_back(Pointi(2,2));
	points.push_back(Pointi(1,3));
	points.push_back(Pointi(1,4));
	points.push_back(Pointi(1,5));
	points.push_back(Pointi(1,6));
		points.push_back(Pointi(0,7));
		points.push_back(Pointi(2,7));
	points.push_back(Pointi(1,8));
	points.push_back(Pointi(1,9));

	size_t s = points.size();
	for (size_t i = 0; i < s; i++) {
		int x = points[i].x;
		int y = points[i].y;
		x += w/2;
		y += h/2;
		field[getIdFromPos(x, y)] = true;
	}
}
