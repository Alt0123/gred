#include "DeleteCommand.h"

DeleteCommand::DeleteCommand(Picture* p)
	:picture_ptr(p)
{}

void DeleteCommand::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Delete)
    {
        complete = picture_ptr->DeleteFigure();
    }
}

