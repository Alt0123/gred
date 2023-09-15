#pragma once
#include <QtWidgets>

class Command
{
public:
	virtual void mouseMoveEvent(QMouseEvent* event) = 0;

	virtual void mousePressEvent(QMouseEvent* event) = 0;

	virtual void mouseReleaseEvent(QMouseEvent* event) = 0;

	virtual void keyPressEvent(QKeyEvent* event) = 0;
};

