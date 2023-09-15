#include "Ellipse.h"

Ellipse_::Ellipse_(const Ellipse_& el)
: Figure(el.b_touch, el.width, el.color)
, centre(el.centre)
, a(el.a)
, b(el.b)
, m_angle(el.m_angle)
{};

Ellipse_::Ellipse_(const Point& centre_, int a_, int b_, double angle_, bool b_touch_, int width_, QColor color_)
: Figure(b_touch_, width_, color_)
, centre(centre_)
, a(a_)
, b(b_)
, m_angle(angle_)
{};

Ellipse_::Ellipse_(const Point& centre_, int a_, int b_, double angle_)
: Figure(centre_.GetTouch(), centre_.GetWidth(), centre_.GetColor())
, centre(centre_)
, a(a_)
, b(b_)
, m_angle(angle_)
{};

Ellipse_::Ellipse_(const Point& centre_, int a_, int b_)
: Figure(centre_.GetTouch(), centre_.GetWidth(), centre_.GetColor())
, centre(centre_)
, a(a_)
, b(b_)
, m_angle(0)
{};



std::vector<std::shared_ptr<Prim::Figure>> Ellipse_::DecomposeFigure() const
{

	std::vector<std::shared_ptr<Prim::Figure>> set;
	set.push_back(std::make_shared<Prim::Ellipse>(Prim::Point(centre.GetX(), centre.GetY()), a, b, m_angle));

	if (b_touch)
	{
		Point hot_p1(centre.GetX() + a, centre.GetY()); hot_p1.MoveAngle(m_angle); // передача хотпоинтов происходит с учетом угла поворота
		Point hot_p2(centre.GetX(), centre.GetY() + b); hot_p2.MoveAngle(m_angle);
		set.push_back(std::make_shared<Prim::Point>(Prim::Point(hot_p1.GetX(), hot_p1.GetY())));
		set.push_back(std::make_shared<Prim::Point>(Prim::Point(hot_p2.GetX(), hot_p1.GetY())));
	}

	return set;

}


PointT Ellipse_::GetMaxXY() const
{

	if (!m_angle)
		return PointT(centre.GetX() + a, centre.GetY() + b);

	if (m_angle == 90 || m_angle == -90)
		return PointT(centre.GetX() + b, centre.GetY() + a);

	return PointT(centre.GetX() + std::max(a, b), centre.GetY() + std::max(a, b)); //если угол поворота не 0 и не 90, ?

}


//bool Ellipse::IsBelongs(PointT point_) const
//{
//
//	double angleradian = m_angle * 3.1415926535 / 180;
//	int x = point_.first;
//	int y = point_.second;
//	int x0 = centre.GetX();
//	int y0 = centre.GetY();
//
//	double numerator1 = cos(angleradian) * (x - x0) + sin(angleradian) * (y - y0);
//	numerator1 *= numerator1;
//	double numerator2 = sin(angleradian) * (x - x0) - cos(angleradian) * (y - y0);
//	numerator2 *= numerator2;
//
//	double result = numerator1 / (a * a) + numerator2 / (b * b);
//	return (round(result) == 1);
//
//}

//Вспомогательная функция 
double initialAngle(double a, double b, double x, double y) 
{

	auto abs_x = fabs(x);
	auto abs_y = fabs(y);
	bool isOutside = false;
	if (abs_x > a || abs_y > b) isOutside = true;

	double xd, yd;
	if (!isOutside) {
		xd = sqrt((1.0 - y * y / (b * b)) * (a * a));
		if (abs_x > xd)
			isOutside = true;
		else {
			yd = sqrt((1.0 - x * x / (a * a)) * (b * b));
			if (abs_y > yd)
				isOutside = true;
		}
	}
	double t;
	if (isOutside)
		t = atan2(a * y, b * x); //The point is outside of ellipse
	else {
		//The point is inside
		if (xd < yd) {
			if (x < 0) xd = -xd;
			t = atan2(y, xd);
		}
		else {
			if (y < 0) yd = -yd;
			t = atan2(yd, x);
		}
	}
	return t;

}

// Функция, которая считает расстояние от точки до эллипса - используется лишь в IsBelongs 
double distanceToElipse(double a, double b, double x, double y, int maxIter = 10, double maxError = 1e-5) 
{

	auto a2mb2 = a * a - b * b;
	double t = initialAngle(a, b, x, y);
	auto ct = cos(t);
	auto st = sin(t);

	int i;
	double err;
	for (i = 0; i < maxIter; i++) {
		auto f = a2mb2 * ct * st - x * a * st + y * b * ct;
		auto fp = a2mb2 * (ct * ct - st * st) - x * a * ct - y * b * st;
		auto t2 = t - f / fp;
		err = fabs(t2 - t);
		t = t2;
		ct = cos(t);
		st = sin(t);
		if (err < maxError) break;
	}
	auto dx = a * ct - x;
	auto dy = b * st - y;

	return   sqrt(dx * dx + dy * dy);

}


bool Ellipse_::IsBelongs(PointT point_) const
{
	double TOL = 3.0;
	if (width > 6)
		TOL = width / 2.0;

	//пересчет координат - функция distanceToElipse принимает координаты относительно центра эллипса
	double x = point_.first - centre.GetX();
	double y = point_.second - centre.GetY();

	//расстояние от точки до эллипса
	double dist = distanceToElipse(a, b, x, y); 

	return (dist < TOL);

}

std::shared_ptr<Figure> Ellipse_::CreateCopy() const
{
	return std::make_shared<Ellipse_>(Ellipse_(centre, a, b, m_angle, b_touch, width, color));
}
