#include "Point.h"

Point::Point(const Point& p)
: Figure(p.b_touch, p.width, p.color)
, x(p.x)
, y(p.y)
{};


Point::Point(int x_, int y_, bool b_touch_, int width_, QColor color_)
: Figure(b_touch_, width_, color_)
, x(x_)
, y(y_)
{};

Point::Point(int x_, int y_)
: Figure()
, x(x_)
, y(y_)
{};



void Point::Move(PointT delta)
{
	x += delta.first;
	y += delta.second;
}


std::vector<std::shared_ptr<Prim::Figure>> Point::DecomposeFigure() const
{
	std::vector<std::shared_ptr<Prim::Figure>> set;
	set.push_back(std::make_shared<Prim::Point>(x,y));
	return set;
}


PointT Point::GetCenter() const
{

   return PointT(x, y);

}


PointT Point::GetMaxXY() const
{

   return PointT(x, y);

}


//bool Point::IsBelongs(const PointT& point_) const
//{
//
//	return (point_.first == x && point_.second == y);
//
//}


bool Point::IsBelongs(PointT point_) const
{

	double x2 = point_.first;
	double y2 = point_.second;
	double dist = sqrt((x2 - x) * (x2 - x) + (y2 - y) * (y2 - y)); //расстояние от точки до точки
	
	// Попадание в пределах порога
	double TOL = 3.0;
	if (width > 6)
		TOL = width / 2.0;
	return (dist < TOL);

}


void Point::PointMoveAngle(const PointT& point_, double angle) 
{

	double x0 = point_.first;
	double y0 = point_.second;
	double angleradian = qDegreesToRadians(angle);
	int newX = x0 + round((x - x0) * cos(angleradian) - (y - y0) * sin(angleradian));
	int newY = y0 + round((x - x0) * sin(angleradian) + (y - y0) * cos(angleradian));

	x = newX;
	y = newY;

}

std::shared_ptr<Figure> Point::CreateCopy() const
{
	return std::make_shared<Point>(Point(x, y, b_touch, width, color));
}
