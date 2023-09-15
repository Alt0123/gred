#include "Triangle.h"

Triangle::Triangle()
: Figure()
, left_bot()
, top()
, right_bot()
{};

Triangle::Triangle(const Triangle& tr)
: Figure(tr.b_touch, tr.width, tr.color)
, left_bot(tr.left_bot)
, top(tr.top)
, right_bot(tr.right_bot)
{};

Triangle::Triangle(const Point& left_bot_, const Point& top_, const Point& right_bot_, bool b_touch_, int width_, QColor color_)
: Figure(b_touch_, width_, color_)
, left_bot(left_bot_)
, top(top_)
, right_bot(right_bot_)
{};

Triangle::Triangle(const Point& left_bot_, const Point& top_, const Point& right_bot_)
: Figure(left_bot_.GetTouch(),left_bot_.GetWidth(),left_bot_.GetColor())
, left_bot(left_bot_)
, top(top_)
, right_bot(right_bot_)
{};


void Triangle::Move(PointT delta)
{

	left_bot.Move(delta);
	top.Move(delta);
	right_bot.Move(delta);

}


std::vector<std::shared_ptr<Prim::Figure>> Triangle::DecomposeFigure() const
{
	std::vector<std::shared_ptr<Prim::Figure>> set;
	Prim::Point point1(left_bot.GetX(), left_bot.GetY()); //левая точка основания
	Prim::Point point2(top.GetX(), top.GetY()); //верхняя точка
	Prim::Point point3(right_bot.GetX(), right_bot.GetY()); //правая точка основания

	set.push_back(std::make_shared<Prim::Line>(point1, point2)); //левая боквая сторона
	set.push_back(std::make_shared<Prim::Line>(point2, point3)); //правая боковая сторона
	set.push_back(std::make_shared<Prim::Line>(point3, point1)); //основание
	if (b_touch)
	{
		set.push_back(std::make_shared<Prim::Point>(point1));
		set.push_back(std::make_shared<Prim::Point>(point2));
		set.push_back(std::make_shared<Prim::Point>(point3));

	}
	return set;
}

PointT Triangle::GetCenter() const
{
	int x1 = left_bot.GetX();
	int x2 = top.GetX();
	int x3 = right_bot.GetX();

	int y1 = left_bot.GetX();
	int y2 = top.GetX();
	int y3 = right_bot.GetX();

	int x = round(static_cast<double>(x1 + x2 + x3) / 3.0);
	int y = round(static_cast<double>(y1 + y2 + y3) / 3.0);

	return { x,y };
}


//поиск максимальных координат из 3 точек 
PointT Triangle::GetMaxXY() const
{

	int a = left_bot.GetX();
	int b = top.GetX();
	int c = right_bot.GetX();
	int maximumX = std::max(a, std::max(b, c));
	a = left_bot.GetY();
	b = top.GetY();
	c = right_bot.GetY();
	int maximumY = std::max(a, std::max(b, c));
	return PointT(maximumX, maximumY);

}


bool Triangle::IsBelongs(PointT point_)  const
{

	Line side1(left_bot, top); side1.SetWidth(width); //задается толщина линии для корректной работы метода IsBelongs
	Line side2(top, right_bot); side2.SetWidth(width);
	Line bot(right_bot, left_bot); bot.SetWidth(width);
	return (side1.IsBelongs(point_) || top.IsBelongs(point_) || side2.IsBelongs(point_) || bot.IsBelongs(point_));

}


void Triangle::MoveAngle(double angle)
{
	//поворот фигуры осуществляется засчет поворота каждой точки относительно центра
	auto cnt = GetCenter();
	left_bot.PointMoveAngle(cnt, angle);
	top.PointMoveAngle(cnt, angle);
	right_bot.PointMoveAngle(cnt, angle);

}


void Triangle::SetEnd(PointT p)
{

	right_bot = Point(p.first, p.second); 
	//координата левой нижней вершины - это координата верхней вершины -(минус) расстояние от неё до правой нижней вершины
	left_bot = Point(top.GetX() - (p.first - top.GetX()), p.second);

}

std::shared_ptr<Figure> Triangle::CreateCopy() const
{
	return std::make_shared<Triangle>(Triangle(left_bot, top, right_bot, b_touch, width, color));
}
