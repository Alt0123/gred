#include "Circle.h"
/////
Circle::Circle()
: Figure()
, centre()
, radius(0)
{};

Circle::Circle(const Circle& c)
: Figure(c.b_touch, c.width, c.color)
, centre(c.centre)
, radius(c.radius)
{};

Circle::Circle(const Point& centre_, int radius_, bool b_touch_, int width_, QColor color_)
: Figure(b_touch_, width_, color_)
, centre(centre_)
, radius(radius_)
{};


Circle::Circle(const Point& centre_, int radius_)
: Figure(centre_.GetTouch(), centre_.GetWidth(), centre_.GetColor())
, centre(centre_)
, radius(radius_)
{};



std::vector<std::shared_ptr<Prim::Figure>> Circle::DecomposeFigure() const
{

	std::vector<std::shared_ptr<Prim::Figure>> set;
	set.push_back(std::make_shared<Prim::Ellipse>(Prim::Point(centre.GetX(), centre.GetY()), radius, radius, 0));

	if (b_touch)
	{
		set.push_back(std::make_shared<Prim::Point>(Prim::Point(centre.GetX() + radius, centre.GetY())));
	}

	return set;

}


PointT Circle::GetMaxXY() const
{

	return PointT(centre.GetX() + radius,centre.GetY() + radius);

}


bool Circle::IsBelongs(PointT point_) const
{

	int x = point_.first;
	int y = point_.second;
	int x0 = centre.GetX();
	int y0 = centre.GetY();

	Line line (Point(x, y), Point(x0, y0));
	int length = line.Length();

	double TOL = 3.0;
	if (width > 6)
		TOL = width / 2.0;

	//return ((x - x0) * (x - x0) + (y - y0) * (y - y0) == radius * radius);
	/*bool tmp1 = (x - x0) * (x - x0) + (y - y0) * (y - y0) >= (radius - TOL) * (radius - TOL);
	bool tmp2 = (x - x0) * (x - x0) + (y - y0) * (y - y0) <= (radius + TOL) * (radius + TOL);*/
	
	return (length >= radius - TOL) && (length <= radius + TOL);

}


void Circle::SetEnd(PointT p)
{

	Line line(this->GetCentre(),Point(p.first,p.second));
	radius = line.Length();

}

std::shared_ptr<Figure> Circle::CreateCopy() const
{
	return std::make_shared<Circle>(Circle(centre, radius, b_touch, width, color));
}
	
