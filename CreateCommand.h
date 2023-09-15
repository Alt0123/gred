#pragma once
#include <QtWidgets>

#include "Picture.h"
#include "Command.h"
#include "Point.h"
#include "Line.h"
#include "Circle.h"
#include "Square.h"
#include "Triangle.h"
#include "Ellipse.h"

enum class FigureType
{
	Point = 0,
	Line,
	Polyline,
	Triangle,
	Square,
	Ellipse,
	Circle
};


class CreateCommand : public Command
{
private:
	Picture* picture_ptr {};
	FigureType type;
	std::shared_ptr<Figure> cur_fig {};

public:
	CreateCommand ( Picture*);
	
	void mouseMoveEvent(QMouseEvent* event) override;

	void mousePressEvent(QMouseEvent* event) override;

	void mouseReleaseEvent(QMouseEvent* event) override {};

	void keyPressEvent(QKeyEvent* event) override {};

	void setFigureType(const int n) { type = static_cast<FigureType>(n); };
};

