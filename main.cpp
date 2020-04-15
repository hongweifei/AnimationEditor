


#include "window/FlyWindow.h"

#undef main

int main()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	FlyWindow *window = new FlyWindow("0");
	FlyWindow *window1 = new FlyWindow("1");
	FlyWindow* window2 = new FlyWindow("2");
	FlyWindow* window3 = new FlyWindow("3");
	FlyWindow* window4 = new FlyWindow("4");
	FlyWindow* window5 = new FlyWindow("5");
	FlyWindow* window6 = new FlyWindow("6");
	FlyWindow* window7 = new FlyWindow("7");

	window->Create(WINDOW_OPENGL);
	window1->Create(WINDOW_OPENGL);
	window2->Create(WINDOW_OPENGL);
	window3->Create(WINDOW_OPENGL);
	window4->Create(WINDOW_OPENGL);
	window5->Create(WINDOW_OPENGL);
	window6->Create(WINDOW_OPENGL);
	window7->Create(WINDOW_OPENGL);

	WindowsMainLoop(8, window, window1, window2, window3, window4, window5, window6, window7);

	return 0;
}


