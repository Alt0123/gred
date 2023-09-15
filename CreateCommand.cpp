#include <memory>

#include "CreateCommand.h"


CreateCommand::CreateCommand(Picture* p)
	:picture_ptr(p)
{}

void CreateCommand::mouseMoveEvent(QMouseEvent* event)
{
	if (cur_fig && type != FigureType::Point)
	{
		cur_fig->SetEnd({ event->position().x(), event->position().y() });
	}
}

void CreateCommand::mousePressEvent(QMouseEvent* event)
{
	switch (type)
	{
	case FigureType::Point:
		cur_fig = picture_ptr->AddFigure(* new Point(event->position().x(), event->position().y(), false, 15, Qt::black));
		break;
	case FigureType::Line:
		cur_fig = picture_ptr->AddFigure(* new Line(Point(event->position().x(), event->position().y(), false, 15, Qt::black),
													Point(event->position().x(), event->position().y(), false, 15, Qt::black)));
		break;
	case FigureType::Polyline:
		//p.AddFigure(std::make_shared<Polyline>());
		break;
	case FigureType::Triangle:
		cur_fig = picture_ptr->AddFigure(*new Triangle(Point(event->position().x(), event->position().y(), false, 15, Qt::black),
			Point(event->position().x(), event->position().y(), false, 15, Qt::black),
			Point(event->position().x(), event->position().y(), false, 15, Qt::black)));
		break;
	case FigureType::Square:
		cur_fig = picture_ptr->AddFigure(*new Square(Point(event->position().x(), event->position().y(), false, 15, Qt::black),
													Point(event->position().x(), event->position().y(), false, 15, Qt::black)));										 
		break;
	case FigureType::Ellipse:
		cur_fig = picture_ptr->AddFigure(*new Ellipse_(Point(event->position().x(), event->position().y(), false, 15, Qt::black), 0, 0));
		break;
	case FigureType::Circle:
		cur_fig = picture_ptr->AddFigure(*new Circle(Point(event->position().x(), event->position().y(), false, 15, Qt::black), 0 ));
		break;
	default:
		break;
	}
}

