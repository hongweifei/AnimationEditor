#pragma once


#include "../FlyRenderer.h"

#ifndef WIDGET
#define WIDGET


class Widget
{
public:
	Widget(int = 0,int = 0,int = 0,int = 0);
	~Widget();

	virtual void Render(FlyRenderer*);
private:
	int x;
	int y;
	int width;
	int height;
};






#endif // !WIDGET
