


#include "window/FlyWindow.h"

#undef main

int main()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	FlyWindow *window = new FlyWindow("Title");

	window->Create(WINDOW_OPENGL);
	window->MainLoop();

	return 0;
}


