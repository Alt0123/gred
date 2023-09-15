#include "TouchCommand.h"

TouchCommand::TouchCommand(Picture* pic)
	:picture_ptr(pic)
{}

void TouchCommand::mousePressEvent(QMouseEvent* event)
{
	qDebug() << "Is touch ";
	if (picture_ptr->ZeroTouch())
	{
		complete = true;
	}
	else
	{
		complete = false;
	}
	auto ptr = picture_ptr->GetFigure({ event->position().x(), event->position().y() });
	if (ptr)
	{
		if (!ptr->GetTouch())
		{
			ptr->SetTouch(true);
			complete = true;
		}
		else complete = false;
	}

}
