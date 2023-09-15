#include "MoveCommand.h"

MoveCommand::MoveCommand(Picture& p)
	:picture_ptr{&p}
{}

void MoveCommand::mouseMoveEvent(QMouseEvent * event)
{
    const QPointF curPos = event->position();
    const PointT delta = { curPos.x() - cur_fig->GetCenter().first, curPos.y() - cur_fig->GetCenter().second };
    cur_fig->Move(delta);
}

void MoveCommand::mousePressEvent(QMouseEvent* event)
{
    PointT pos{ event->position().x(), event->position().y() };

    cur_fig = picture_ptr->GetFigure( pos );
    if (cur_fig)
    {
        if (!cur_fig->IsBelongs(pos))
        {
            cur_fig->SetTouch(false);
        }
    }
}

