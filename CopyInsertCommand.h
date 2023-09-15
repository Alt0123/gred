#pragma once
#include "Command.h"

#include <memory>
#include "Picture.h"
#include "Figure.h"


class CopyInsertCommand : public Command
{
private:
	Picture* pic;
	std::shared_ptr<Figure> copied_fig;

public:
	CopyInsertCommand(Picture*);

	void Copy();

	void Insert();

	void mouseMoveEvent(QMouseEvent* event) override {};

	void mousePressEvent(QMouseEvent* event) override {};

	void mouseReleaseEvent(QMouseEvent* event) override {};

	void keyPressEvent(QKeyEvent* event) override {};
};

