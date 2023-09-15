#pragma once
#include <QWidget>
#include <QPainter>
#include "Figure.h"
#include "Picture.h"

/// <summary>
/// DrawLabel - класс для рисования рисунка и фигур. Он универсальный, 
/// при передачи указателя класса Figure, он определяет тип фигуры и рисует её
/// с помощью метода Draw. 
/// В методе Draw у фигуры запрашивается набор примитивов,
/// и они отображаются одинаково для всех фигур(так, чтобы не приходилось
///	выполнять какие - либо специфические операции для конкретных классов фигур).
/// </summary>
class DrawerLabel : public QWidget
{
	Q_OBJECT

public:
	explicit DrawerLabel(QWidget* parent = nullptr) {};
	void draw(QPainter& painter, const Picture& picture) const;
	void drawFigure(QPainter& painter, const Figure& figure) const;
};