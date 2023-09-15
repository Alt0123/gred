#include "Line.h"

Line::Line()
: Figure()
, start()
, end()
{};

Line::Line(const Line& l)
: Figure(l.b_touch, l.width, l.color)
, start(l.start)
, end(l.end)
{};

Line::Line(const Point& start_, const Point& end_, bool b_touch_, int width_, QColor color_)
: Figure(b_touch_, width_, color_)
, start(start_)
, end(end_)
{};

Line::Line(const Point& start_, const Point& end_)
: Figure(start_.GetTouch(),start_.GetWidth(),start_.GetColor())
, start(start_)
, end(end_)
{};



void Line::Move(PointT delta)
{

	start.Move(delta);
	end.Move(delta);

}


std::vector<std::shared_ptr<Prim::Figure>> Line::DecomposeFigure() const
{
	std::vector<std::shared_ptr<Prim::Figure>> set;
	Prim::Point point1(start.GetX(), start.GetY());
	Prim::Point point2(end.GetX(), end.GetY());

	set.push_back(std::make_shared<Prim::Line>(point1, point2));

	if (b_touch)
	{
		set.push_back(std::make_shared<Prim::Point>(point1));
		set.push_back(std::make_shared<Prim::Point>(point2));
	}
	return set;
}


PointT Line::GetCenter() const
{

	return PointT((start.GetX() + end.GetX()) / 2, (start.GetY() + end.GetY()) / 2);

}


PointT Line::GetMaxXY() const
{

	return PointT(std::max(start.GetX(),end.GetX()), std::max(start.GetY(), end.GetY()));

}


//Старая реализация метода - без учета толщины 
//bool Line::IsBelongs(const PointT& point_)  const
//{
//	int  x = point_.first;
//	int x1 = start.GetX();
//	int x2 = end.GetX();
//
//	int  y = point_.second;
//	int y1 = start.GetY();
//	int y2 = end.GetY();
//
//
//	int tempx = (x - x1) * (x2 - x);
//	int tempy = (y - y1) * (y2 - y);
//
//	if ((tempx >= 0 && tempx <= (x1 - x2) * (x1 - x2)) && (tempy >= 0 && tempy <= (y1 - y2) * (y1 - y2)))
//		return  ((x - x1) * (y2 - y1) - (x2 - x1) * (y - y1)) == 0;
//
//	return false;
//
//}


///Метод,который позволяет узнать, принадлежит ли точка отрезку - реализация из ImageViewer
bool Line::IsBelongs(PointT point_)  const
{

	double x0 = point_.first, y0 = point_.second;
	double x1 = start.GetX(), y1 = start.GetY();
	double x2 = end.GetX(), y2 = end.GetY();

	// Вычислим расстояние между точкой и прямой, заданной концами отрезка
	double n = qFabs((y2 - y1) * x0 - (x2 - x1) * y0 + x2 * y1 - y2 * x1);
	double d = qSqrt((y2 - y1) * (y2 - y1) + (x2 - x1) * (x2 - x1));
	if (d == 0.0)
		d = 0.00001;
	double dist = n / d;
	// Попадание в отрезок - в пределах порога
	double TOL = 3.0;
	if (width > 6)
		TOL = width / 2.0;
	return (dist < TOL);

}


void Line::MoveAngle(double angle)
{

	auto cnt = GetCenter();
	start.PointMoveAngle(cnt, angle);
	end.PointMoveAngle(cnt, angle);

}


int Line::IsMarkerHit(PointT point_) const
{

	Point start_ = start; start_.SetWidth(width);
	Point end_ = end; end_.SetWidth(width);

	if (start_.IsBelongs(point_))
		return 1;

	if (end_.IsBelongs(point_))
		return 2;

	return -1;

}


bool Line::MoveMarker(int markerIdx, PointT delta) 
{

	switch (markerIdx)
	{
	case(1):
		start.Move(delta);
		return true;
	case(2):
		end.Move(delta);
		return true;
	default:
		return false;
	}

}


void Line::LineMoveAngle(const PointT& point_, double angle)
{

	start.PointMoveAngle(point_, angle);
	end.PointMoveAngle(point_, angle);

}


int Line::Length() const
{

	int x1 = start.GetX();
	int x2 = end.GetX();
	int y1 = start.GetY();
	int y2 = end.GetY();
	int result = round(sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
	return result;

}

std::shared_ptr<Figure> Line::CreateCopy() const
{
	return std::make_shared<Line>(Line(start, end, b_touch, width, color));
}
