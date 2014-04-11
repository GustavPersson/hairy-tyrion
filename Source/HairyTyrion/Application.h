#pragma once
#include "../Utilities/Macros.h"
#include <SDL.h>
#include <stdio.h>

/*
The main application class.
*/
class Application {
public:
	bool quit;
	SDL_Event event;
	SDL_Window* gWindow;
	SDL_Surface* gScreenSurface;
	SDL_Surface* gCurrentSurface;
	SDL_Surface* gXOut;
	enum KeyPressSurfaces
	{
		KEY_PRESS_SURFACE_DEFAULT,
		KEY_PRESS_SURFACE_UP,
		KEY_PRESS_SURFACE_DOWN,
		KEY_PRESS_SURFACE_LEFT,
		KEY_PRESS_SURFACE_RIGHT,
		KEY_PRESS_SURFACE_TOTAL
	};
	SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

	Application();
	virtual ~Application();

	/*
	Creates an instance of Application
	*/
	static void createInstance();
	
	/*
	Returns an instance of Application
	*/
	static Application* getInstance();

	/*
	To be run on app close. Frees used memory.
	*/
	void onClose();

	/*
	Inits the instance, starts class objects.
	*/
	bool initInstance();

	/*
	Loads media needed by the application
	*/
	bool loadMedia();

	/*
	Loads an image at the specified path.
	*/
	SDL_Surface* loadSurface(std::string path);

	/*
	Main game loop.
	*/
	void runGame();
	
protected:
	static Application * mpsInstance;

};