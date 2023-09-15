#pragma once
#include <QtWidgets>

#include <utility>
#include <memory>

#include "Picture.h"
#include "Command.h"

class DeleteCommand : public Command
{
private:
	Picture* picture_ptr {};
	bool complete {false};

public:
	DeleteCommand(Picture*);

	//Удалятеся выделеная фигура
	void mousePressEvent(QMouseEvent* event) override {};

	void mouseMoveEvent(QMouseEvent* event) override {};

	void mouseReleaseEvent(QMouseEvent* event) override {};

	void keyPressEvent(QKeyEvent* event) override;

	bool GetComplete() { return complete; }
};

