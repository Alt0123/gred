#pragma once

#include <QtWidgets>
#include "DrawerLabel.h"
#include "Line.h"
#include "Point.h"
#include "Picture.h"
#include "TouchCommand.h"
#include "CreateCommand.h"
#include "DeleteCommand.h"
#include "MoveCommand.h"
#include "CopyInsertCommand.h"
#include "MoveAngleCommand.h"

/// <summary>
/// CentralWidget - класс-виджет для отображения и редактирования рисунка. Команды, влияющие
/// на рисунок в целом(например, сохранение и загрузка) отправляются в этот виджет с помощью
/// обработчиков событий Qt(например, в MainWindow эти связи задаются с помощью connect()).
/// В нём будут содержаться методы из группы Mouse Event для обработки действий мыши - здесь
/// они должны преобразовываться в вызовы объектов - контроллеров.
/// </summary>
class CentralWidget : public QWidget
{
	Q_OBJECT

public:

public:
	explicit CentralWidget(Picture& pic, QWidget* parent = nullptr);

	void setFigure(const int t) { c->setFigureType(t); };

	void CopyFig();
	void InsertFig();

	DrawerLabel* drawerLabel{};
	bool b_touch{ false };
	bool b_rotate{ false };
	bool b_draw{ false };
	void keyPressEvent(QKeyEvent* event) override;
private: 
	Picture& picture;
	

private:
	std::unique_ptr<CreateCommand> c;
	std::unique_ptr<DeleteCommand> d;
	std::unique_ptr<CopyInsertCommand> copy_insert;

public slots:
	void moving();
	void rotate();
	void ObjectPresentTouch(bool checked) { b_touch = true; b_rotate = false; b_draw = false; };  //пока что заглушка. функция ObjectPresent, которая проверяет, выполняется ли сейчас построение. Если не выполняется, то делаем выделение.};
	void ObjectPresentRotate(bool checked) { b_rotate = true; b_touch = false; b_draw = false; };


protected:
	void paintEvent(QPaintEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;


};