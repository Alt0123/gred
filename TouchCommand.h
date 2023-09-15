#pragma once
#include <QtWidgets>
#include <memory>

#include "Picture.h"
#include "Command.h"


class TouchCommand : public Command
{
private:
	Picture* picture_ptr{};
	bool complete{ false };

public:
	TouchCommand(Picture*);

	bool GetComplete() { return complete; };

	void mouseMoveEvent(QMouseEvent* event) override {};

	void mousePressEvent(QMouseEvent* event) override;

	void mouseReleaseEvent(QMouseEvent* event) override {};

	void keyPressEvent(QKeyEvent* event) override {};
};

