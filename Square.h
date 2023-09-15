#pragma once

#include "Figure.h"
#include "Line.h"

class Square: public Figure {

	Point left_bot, left_top, right_top, right_bot;

public:
	Square();
	Square(const Square& s);
	Square(const Point& left_bot_, const Point& left_top_, const Point& right_top_, const Point& right_bot_, bool b_touch_, int width_, QColor color_);
	Square(const Point& left_bot_, const Point& left_top_, const Point& right_top_, const Point& right_bot_);
	Square(const Point& left_top_, const Point& right_bot_, bool b_touch_, int width_, QColor color_);
	Square(const Point& left_top_, const Point& right_bot_);

	void Move(PointT delta) override;
	std::vector<std::shared_ptr<Prim::Figure>> DecomposeFigure() const override;
	PointT GetCenter() const override;
	PointT GetMaxXY() const override ;
	bool IsBelongs(PointT point_) const override;
	void MoveAngle(double angle) override ;
	void SetEnd(PointT p) override;
	int IsMarkerHit(PointT pnt) const override { return -1; } ; //заглушка, т.к. реализация нужна лишь для класса line ...override
	bool MoveMarker(int markerIdx, PointT delta) override { return false; }; //заглушка, т.к. реализация нужна лишь для класса line
	std::shared_ptr<Figure> CreateCopy() const override;

	Point GetLeftBot() const { return left_bot; };
	Point GetLeftTop() const { return left_top; };
	Point GetRightTop() const { return right_top; };
	Point GetRightBot() const { return right_bot; };
	void SetLeftBot(const Point& left_bot_) { left_bot = left_bot_; };
	void SetLeftTop(const Point& left_top_) { left_top = left_top_; };
	void SetRightTop(const Point& right_top_) { right_top = right_top_; };
	void SetRightBot(const Point& right_bot_) { right_bot = right_bot_; };
	
};