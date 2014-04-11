//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include "../Utilities/Macros.h"
#include "Application.h"

int main(int argc, char *argv[]) {
	initMemoryCheck();

	Application::createInstance();
	Application* pApp = Application::getInstance();

	if (pApp->initInstance()) {
		pApp->runGame();
		pApp->onClose();
	}

	SAFE_DELETE(pApp);

#pragma warning(push)
#ifdef _DEBUG
#pragma warning(disable: 4189)
	int * banan = myNew int; //bevisa att minnesläckhittaren funkar.
#endif
	return 0;
}
#pragma warning(pop)