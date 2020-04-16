

#include "widget.h"


Widget::Widget(int x, int y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

Widget::~Widget()
{
}


void Widget::Render(FlyRenderer* renderer)
{
	
}