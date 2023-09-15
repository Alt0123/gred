#include "CopyInsertCommand.h"
#include "Point.h"

CopyInsertCommand::CopyInsertCommand(Picture* p)
	:pic(p)
{}

void CopyInsertCommand::Copy()
{
	if (pic->GetFigure())
	{
		copied_fig = pic->GetFigure()->CreateCopy();
	}
}

void CopyInsertCommand::Insert()
{
	if (copied_fig)
	{
		pic->ZeroTouch();
		copied_fig->Move({40, 20});
		pic->AddFigure(copied_fig->CreateCopy());
	}
}
