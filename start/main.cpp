
#include <rt2d/core.h>

#include "myscene.h"
#include "menu.h"

std::vector<Scene*> scenes;
int currentScene = 0;


int main( void )
{
	// Core instance
	Core core;

	// menu
	Menu* scene_menu = new Menu();

	// myscene
	MyScene* scene_game = new MyScene(); // create Scene on the heap

	// credits

	// set scenes in 
	scenes.push_back(scene_menu);
	scenes.push_back(scene_game);


	while(scenes[currentScene]->isRunning()) { // check status of Scene every frame
		core.run(scenes[currentScene]); // update and render the current scene
		core.showFrameRate(5); // show framerate in output every n seconds

		// test if new scene
		if (scenes[currentScene]->sceneDone) {
			std::cout << currentScene << std::endl;
			if (currentScene == 1) {
				Menu* _scene_menu = new Menu(); // create Scene on the heap
				scenes[0] = _scene_menu;
				delete scenes[currentScene];
				currentScene -= 1;
			}else {
				MyScene* _scene_game = new MyScene(); // create Scene on the heap
				scenes[1] = _scene_game;
				delete scenes[currentScene];
				currentScene += 1;
			}
		}
	}
	//core.cleanup(); // cleanup ResourceManager (Textures + Meshes, but not Shaders)
	delete scene_game; // delete Scene and everything in it from the heap to make space for next Scene

	// No need to explicitly clean up the core.
	// As a local var, core will go out of scope and destroy Renderer->ResourceManager.
	// ResourceManager destructor also deletes Shaders.

	return 0;
}
