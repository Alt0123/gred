#include "DrawerLabel.h"
#include "PrimitiveFigure.h"

void DrawerLabel::draw(QPainter& painter, const Picture& picture) const
{
    QPen pen;
    std::vector<std::shared_ptr<Figure>>  figures{};
    picture.GetFigures(figures);
    for (const auto& f : figures)
    {
        pen.setColor(f->GetColor());
        pen.setWidth(f->GetWidth());
        painter.setPen(pen);
        auto c = f->DecomposeFigure();
        for (auto& a : c)
        {
            a->Draw(painter);
        }

    }
}
void DrawerLabel::drawFigure(QPainter& painter, const Figure& figure) const
{
    QPen Pen;
    Pen.setColor(figure.GetColor());
    Pen.setWidth(figure.GetWidth());
    auto c = figure.DecomposeFigure();
    for (auto& a : c)
    {
        a->Draw(painter);
    }
    
}

