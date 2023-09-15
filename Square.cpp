#include "Square.h"

Square::Square()
: Figure()
, left_bot()
, left_top()
, right_top()
, right_bot()
{};

Square::Square(const Square& s)
: Figure(s.b_touch, s.width, s.color)
, left_bot(s.left_bot)
, left_top(s.left_top)
, right_top(s.right_top)
, right_bot(s.right_bot)
{};

Square::Square(const Point& left_bot_, const Point& left_top_, const Point& right_top_, const Point& right_bot_, bool b_touch_, int width_, QColor color_)
: Figure(b_touch_,width_,color_)
, left_bot(left_bot_)
, left_top(left_top_)
, right_top(right_top_)
, right_bot(right_bot_)
{};

Square::Square(const Point& left_bot_, const Point& left_top_, const Point& right_top_, const Point& right_bot_)
: Figure(left_bot_.GetTouch(), left_bot_.GetWidth(), left_bot_.GetColor())
, left_bot(left_bot_)
, left_top (left_top_)
, right_top(right_top_)
, right_bot(right_bot_)
{};

Square::Square(const Point& left_top_, const Point& right_bot_, bool b_touch_, int width_, QColor color_)
: Figure(b_touch_, width_, color_)
, left_bot(left_top_.GetX(),right_bot_.GetY())
, left_top(left_top_)
, right_top(right_bot_.GetX(), left_top_.GetY())
, right_bot(right_bot_)
{};

Square::Square(const Point& left_top_, const Point& right_bot_)
: Figure(left_top_.GetTouch(),left_top_.GetWidth(),left_top_.GetColor())
, left_bot(left_top_.GetX(), right_bot_.GetY())
, left_top(left_top_)
, right_top(right_bot_.GetX(), left_top_.GetY())
, right_bot(right_bot_)
{};



void Square::Move(PointT delta)
{

	left_bot.Move(delta);
	left_top.Move(delta);
	right_top.Move(delta);	
	right_bot.Move(delta);

}


std::vector<std::shared_ptr<Prim::Figure>> Square::DecomposeFigure() const
{
	std::vector<std::shared_ptr<Prim::Figure>> set;
	Prim::Point point1(left_bot.GetX(), left_bot.GetY()); // левый нижний угол
	Prim::Point point2(left_top.GetX(), left_top.GetY()); //левый верхний угол
	Prim::Point point3(right_top.GetX(), right_top.GetY()); // правый верхний угол
	Prim::Point point4(right_bot.GetX(), right_bot.GetY()); // правый нижний угол

	set.push_back(std::make_shared<Prim::Line>(point1, point2));
	set.push_back(std::make_shared<Prim::Line>(point2, point3));
	set.push_back(std::make_shared<Prim::Line>(point3, point4));
	set.push_back(std::make_shared<Prim::Line>(point4, point1));

	if (b_touch)
	{
		set.push_back(std::make_shared<Prim::Point>(point1));
		set.push_back(std::make_shared<Prim::Point>(point2));
		set.push_back(std::make_shared<Prim::Point>(point3));
		set.push_back(std::make_shared<Prim::Point>(point4));
		
	}
	return set;
}


PointT Square::GetCenter() const
{

	Line line(left_top, right_bot); //формирование диагонали
	return line.GetCenter();

}

//поиск максимальных координат из 4 точек 
PointT Square::GetMaxXY() const
{

	int a = left_bot.GetX();
	int b = left_top.GetX();
	int c = right_top.GetX();
	int d = right_bot.GetX();
	int maximumX = std::max(a, std::max(b, std::max(c, d)));
	a = left_bot.GetY();
	b = left_top.GetY();
	c = right_top.GetY();
	d = right_bot.GetY();
	int maximumY = std::max(a, std::max(b, std::max(c, d)));
	return PointT(maximumX, maximumY);

}


bool Square::IsBelongs(PointT point_)  const
{

	Line left(left_bot, left_top); left.SetWidth(width); //задаем толщину линии для корректной работы IsBelongs
	Line top(left_top, right_top); top.SetWidth(width);
	Line right(right_top, right_bot); right.SetWidth(width);
	Line bot(right_bot, left_bot); bot.SetWidth(width);
	return (left.IsBelongs(point_) || top.IsBelongs(point_) || right.IsBelongs(point_) || bot.IsBelongs(point_));

}


void Square::MoveAngle(double angle)
{
	//поворот фигуры осуществляется засчет поворота каждой точки относительно центра
	auto cnt = GetCenter();
	left_bot.PointMoveAngle(cnt, angle);
	left_top.PointMoveAngle(cnt, angle);
	right_top.PointMoveAngle(cnt, angle);
	right_bot.PointMoveAngle(cnt, angle);

}


void Square::SetEnd(PointT p)
{

	right_bot = Point(p.first, p.second);
	left_bot = Point(left_top.GetX(), right_bot.GetY());	
	right_top = Point(right_bot.GetX(), left_top.GetY());

}

std::shared_ptr<Figure> Square::CreateCopy() const
{
	return std::make_shared<Square>(Square(left_bot, left_top, right_top, right_bot, b_touch, width, color));
}
