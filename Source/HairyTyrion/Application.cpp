#include "Application.h"
#include "windows.h"
#include <string.h>
#include <assert.h>


Application* Application::mpsInstance = NULL;

Application::Application() {
	gWindow = NULL;
	gScreenSurface = NULL;
	gCurrentSurface = NULL;
	gXOut = NULL;
	quit = false;
}

void Application::createInstance() {
	assert(mpsInstance == NULL);

	mpsInstance = myNew Application();
}

Application* Application::getInstance() {
	assert(mpsInstance != NULL);
	return mpsInstance;
}

bool Application::initInstance() {
	bool success = true;
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		//Create window
		gWindow = SDL_CreateWindow("Beerjeweled", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}
	//Load needed media
	success = loadMedia();

	//Set default current surface
	gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];


	return success;
}

bool Application::loadMedia() {
	//Loading success flag
	/*bool success = true;

	//Load splash image
	gXOut = SDL_LoadBMP("assets/x.bmp");
	if (gXOut == NULL) {
		printf("Unable to load image %s! SDL Error: %s\n", "assets/x.bmp", SDL_GetError());
		success = false;
	}
	*/
	//Loading success flag
	bool success = true;

	//Load default surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("assets/press.bmp");
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL)
	{
		printf("Failed to load default image!\n");
		success = false;
	}

	//Load up surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("assets/up.bmp");
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL)
	{
		printf("Failed to load up image!\n");
		success = false;
	}

	//Load down surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("assets/down.bmp");
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL)
	{
		printf("Failed to load down image!\n");
		success = false;
	}

	//Load left surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("assets/left.bmp");
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL)
	{
		printf("Failed to load left image!\n");
		success = false;
	}

	//Load right surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("assets/right.bmp");
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL)
	{
		printf("Failed to load right image!\n");
		success = false;
	}

	return success;
}

SDL_Surface* Application::loadSurface(std::string path)
{
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}

	return loadedSurface;
}


void Application::runGame() {
	while (!quit) {
		//Handle events on queue
		while (SDL_PollEvent(&event) != 0) {
			//User requests quit
			if (event.type == SDL_QUIT) {
				quit = true;
			}
			else if (event.type == SDL_KEYDOWN)
			{
				//Select surfaces based on key press
				switch (event.key.keysym.sym)
				{
				case SDLK_UP:
					gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
					break;
				case SDLK_DOWN:
					gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
					break;
				case SDLK_LEFT:
					gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
					break;
				case SDLK_RIGHT:
					gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
					break;
				default:
					gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
					break;
				}
			}

		}

		//Apply the current image
		SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);

		//Update the surface
		SDL_UpdateWindowSurface(gWindow);
	}
}

void Application::onClose() {
	//Deallocate surface
	SDL_FreeSurface(gXOut);
	gXOut = NULL;

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

Application::~Application() {
	mpsInstance = NULL;
}
