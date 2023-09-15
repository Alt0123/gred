#pragma once

#include "Figure.h"
#include "Line.h"

class Triangle : public Figure {

	Point left_bot, top, right_bot;
public:
	Triangle();
	Triangle(const Triangle& tr);
	Triangle(const Point& left_bot_, const Point& top_, const Point& right_bot_, bool b_touch_, int width_, QColor color_);
	Triangle(const Point& left_bot_, const Point& top_, const Point& right_bot_);

	void Move(PointT delta) override;
	std::vector<std::shared_ptr<Prim::Figure>> DecomposeFigure() const override;
	PointT GetCenter() const override;
	PointT GetMaxXY() const override;
	bool IsBelongs(PointT point_) const override;
	void MoveAngle(double angle) override;
	void SetEnd(PointT p) override;
	int IsMarkerHit(PointT pnt) const override { return -1; }; //заглушка, т.к. реализация нужна лишь для класса line
	bool MoveMarker(int markerIdx, PointT delta) override { return false; }; //заглушка, т.к. реализация нужна лишь для класса line
	std::shared_ptr<Figure> CreateCopy() const override;

	Point GetLeftBot() const { return left_bot; };
	Point GetTop() const { return top; };
	Point GetRightBot() const { return right_bot; };
	void SetLeftBot(const Point& left_bot_) { left_bot = left_bot_; };
	void SetTop(const Point& top_) { top = top_; };
	void SetRightBot(const Point& right_bot_) { right_bot = right_bot_; };

};