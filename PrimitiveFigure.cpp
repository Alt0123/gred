#include "PrimitiveFigure.h"

//---------------------
//Точка
//---------------------
using namespace Prim;

Point::Point(int x, int y)
    : x(x)
    , y(y)
{}

void Point::Draw(QPainter& painter) const
{
    painter.drawPoint(x, y);
}


//---------------------
//Линия
//---------------------

Line::Line(Point a, Point b)
    : start(a)
    , end(b)
{}

void Line::Draw(QPainter& painter) const
{
    painter.drawLine(start.GetX(), start.GetY(), end.GetX(), end.GetY());
}


//---------------------
//Эллипс
//---------------------

Ellipse::Ellipse(Point c, int a, int b, int angle)
    : a(a)
    , b(b)
    , center(c)
    , m_angle(angle)
{}

void Ellipse::Draw(QPainter& painter) const
{
    
    painter.rotate(m_angle);
    painter.drawEllipse(QPointF(center.GetX(), center.GetY()), a, b);
    painter.rotate(-m_angle);
}


