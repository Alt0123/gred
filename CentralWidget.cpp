#include "CentralWidget.h"
#include "DrawerLabel.h"
#include <vector>

CentralWidget::CentralWidget(Picture& pic, QWidget* parent)
        : QWidget(parent)
        , picture(pic)
{
    setMinimumSize(500, 500);
    drawerLabel = new DrawerLabel;
    c = std::make_unique<CreateCommand>(&picture);
    d = std::make_unique<DeleteCommand>(&picture);
    copy_insert = std::make_unique<CopyInsertCommand>(&picture);
}

void CentralWidget::CopyFig()
{
    copy_insert->Copy();
}

void CentralWidget::InsertFig()
{
    copy_insert->Insert();
    update();
}

void CentralWidget::keyPressEvent(QKeyEvent* event)
{
    d->keyPressEvent(event);
    update();
}

void CentralWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    drawerLabel->draw(painter, picture);
}



// Вычисление угла в градусах по двум сторонам прямоугольного треугольника
static double getAngleDegInTr(const PointT& sides)
{
    double radAngle = qAtan2(sides.first, sides.second);
    return qRadiansToDegrees(radAngle);
}


void CentralWidget::mousePressEvent(QMouseEvent* event)
{
    TouchCommand touch(&picture);
    QPainter painter(this);
    if (b_touch || b_rotate)
    {
        touch.mousePressEvent(event);
        if (touch.GetComplete())
        {
            drawerLabel->draw(painter, picture);
            update();
        }
    }
    else if (b_draw)
    {
        c->mousePressEvent(event);
        update();
    }

}


void CentralWidget::moving()
{
    b_touch = false;
}

void CentralWidget::rotate()
{
    b_touch = false;
}

void CentralWidget::mouseMoveEvent(QMouseEvent* event)
{
    if (b_rotate)
    {
        MoveAngleCommand rotate(&picture);
        rotate.mouseMoveEvent(event);
        picture.m_prevPos = { event->position().x(), event->position().y() };
        update();

    }
    else if (b_draw)
    {
        c->mouseMoveEvent(event);
        update();
    }

}
