#include "MoveAngleCommand.h"

MoveAngleCommand::MoveAngleCommand(Picture* pic)
	:picture_ptr(pic)
{}


// ���������� ���� � �������� �� ���� �������� �������������� ������������
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


    // ��������� ���� ����� �������� (������� �������� - ����� ������ � ������� ����)
    // � �������������� ������������.
    const PointT cntFig = pSelectedFig->GetCenter();
    double degAngleCur = getAngleDegInTr({ event->position().x() - cntFig.first, event->position().y() - cntFig.second });
    double degAnglePrev = getAngleDegInTr({ picture_ptr->m_prevPos.first - cntFig.first, picture_ptr->m_prevPos.second - cntFig.second });
    // ���� deltaAngle - �� ������� �������� ���� ��������� ������ ������ ������ 
    // ��� ������� �������� ���� (�� ���������� ����� m_prevPos � 
    // ������� ����� event->position())
    double deltaAngle = degAngleCur - degAnglePrev;


    pSelectedFig->MoveAngle(-deltaAngle);
}
