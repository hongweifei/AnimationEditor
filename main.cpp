

#include "system.h"
#include "window/FlyWindow.h"


#ifdef _WIN32
#undef main
#endif // _WIN32


void WindowRender(FlyRenderer *renderer)
{
	renderer->DrawImageBMP((char*)"E:/C++Projects/AnimationEditor/Debug/image1.bmp",0,0,400,600);
	renderer->DrawImageBMP((char*)"E:/C++Projects/AnimationEditor/Debug/image2.bmp", 400, 0, 400, 600);
}


int main()
{
	SystemInit(INIT_VIDEO|INIT_EVENTS);

	FlyWindow *window = new FlyWindow("AnimationEditor");

	/*
	FlyWindow *window1 = new FlyWindow("1");
	FlyWindow *window2 = new FlyWindow("2");
	FlyWindow *window3 = new FlyWindow("3");
	FlyWindow *window4 = new FlyWindow("4");
	FlyWindow *window5 = new FlyWindow("5");
	FlyWindow *window6 = new FlyWindow("6");
	FlyWindow *window7 = new FlyWindow("7");
	*/

	window->Create(WINDOW_OPENGL|WINDOW_RESIZABLE);

	window->SetRenderEvent(WindowRender);

	/*
	window1->Create(WINDOW_OPENGL);
	window2->Create(WINDOW_OPENGL);
	window3->Create(WINDOW_OPENGL);
	window4->Create(WINDOW_OPENGL);
	window5->Create(WINDOW_OPENGL);
	window6->Create(WINDOW_OPENGL);
	window7->Create(WINDOW_OPENGL);
	*/

	WindowsMainLoop(1, window);

	return 0;
}


