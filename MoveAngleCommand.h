#pragma once
#include <QtWidgets>
#include <memory>

#include "Picture.h"
#include "Command.h"


class MoveAngleCommand : public Command
{
private:
	Picture* picture_ptr{};

public:
	MoveAngleCommand(Picture*);


	void mouseMoveEvent(QMouseEvent* event) override ;

	void mousePressEvent(QMouseEvent* event) override {};

	void mouseReleaseEvent(QMouseEvent* event) override {};

	void keyPressEvent(QKeyEvent* event) override {};
};

#pragma once
