#include "Figure.h"

Figure::Figure(bool b_touch_, int width_, QColor color_)
: b_touch(b_touch_)
, width(width_)
, color(color_)
{}

void Figure::SetColor(QColor color_)
{ 
	color = color_;
}

void Figure::SetWidth(int width_) 
{
	width = width_;
}

void Figure::SetTouch(bool b_touch_)
{
	b_touch = b_touch_;
}

int Figure::GetWidth() const 
{
	return width;

}

QColor Figure::GetColor() const
{
	return color;
}

bool Figure::GetTouch() const
{
	return b_touch;
}