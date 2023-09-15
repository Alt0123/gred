#pragma once

#include <memory>
#include <QtWidgets>

#include "Command.h"
#include "Picture.h"


class MoveCommand : public Command
{
private:
	std::shared_ptr<Picture> picture_ptr{};
	std::shared_ptr<Figure> cur_fig{};

public:
	MoveCommand(Picture&);

	void mouseMoveEvent(QMouseEvent* event) override;

	void mousePressEvent(QMouseEvent* event) override;

	void mouseReleaseEvent(QMouseEvent* event) override {};

	void keyPressEvent(QKeyEvent* event) override {};
};

