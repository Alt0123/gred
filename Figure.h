#pragma once
#include <iostream>
#include <QColor>
#include <vector>
#include <cmath>
#include "PrimitiveFigure.h"

using PointT = std::pair<int, int>;

/// Базовый класс Фигура
class Figure {

protected:
	bool b_touch{ false };
	///Толщина линии
	int width{ 10 };           
	QColor color{ Qt::black };

public:
	Figure() = default;
	Figure(bool b_touch_, int width_, QColor color_);

	void SetColor(QColor color_);
	void SetWidth(int width_);
    void SetTouch(bool b_touch_);
	int GetWidth() const;
	QColor GetColor() const;
	bool GetTouch() const;

	/// Виртуальный метод - разложение фигуры на примитивы
	virtual std::vector<std::shared_ptr<Prim::Figure>> DecomposeFigure() const = 0;
	///Виртуальный метод - перемещение фигуры 
	virtual void Move(PointT delta) = 0;
	///Виртуальный метод - возвращает точку - центр фигуры
	virtual PointT GetCenter() const = 0;
	/// Виртуальный метод - получение максимальных x,y координат, имеющихся в фигуре
	virtual PointT GetMaxXY() const = 0;
	/// Виртуальный метод - проверка, принадлежит ли точка фигуре
	virtual bool IsBelongs(PointT point_) const = 0;
	/// Виртуальный метод - поворот фигуры на определенный угол относительно центра фигуры
	virtual void MoveAngle(double) = 0;
	/// Виртуальный метод - задает конечную точку построения
	virtual void SetEnd(PointT) = 0;
	/// Виртуальный метод - возвращает индекс маркера фигуры, в который попала точка, либо -1, если попадания не было
	virtual int IsMarkerHit(PointT pnt) const = 0;
	/// Виртуальный метод - перемещение конкретного маркера, маркер определяется индексу
	virtual bool MoveMarker(int markerIdx, PointT delta) = 0;
	///Виртуальный метод - создание копии фигуры
	virtual std::shared_ptr<Figure> CreateCopy() const = 0;
    
    virtual ~Figure() = default;
};


