#include "MoveAngleCommand.h"

MoveAngleCommand::MoveAngleCommand(Picture* pic)
	:picture_ptr(pic)
{}


// ¬ычисление угла в градусах по двум сторонам пр€моугольного треугольника
static double getAngleDegInTr(const PointT& sides)
{
    double radAngle = qAtan2(sides.first, sides.second);
    return qRadiansToDegrees(radAngle);
}

void MoveAngleCommand::mouseMoveEvent(QMouseEvent* event)
{
    auto pSelectedFig = picture_ptr->GetFigure();
    if (!pSelectedFig)
    {
        return;
    }


    // ¬ычисл€ем угол между отрезком (вершины которого - центр фигуры и позици€ мыши)
    // и горизонтальным направлением.
    const PointT cntFig = pSelectedFig->GetCenter();
    double degAngleCur = getAngleDegInTr({ event->position().x() - cntFig.first, event->position().y() - cntFig.second });
    double degAnglePrev = getAngleDegInTr({ picture_ptr->m_prevPos.first - cntFig.first, picture_ptr->m_prevPos.second - cntFig.second });
    // ”гол deltaAngle - на сколько градусов надо повернуть фигуру вокруг центра 
    // при текущем смещении мыши (из предыдущей точки m_prevPos в 
    // текущую точку event->position())
    double deltaAngle = degAngleCur - degAnglePrev;


    pSelectedFig->MoveAngle(-deltaAngle);
}
