#pragma once
#include "Figure.h"

class Point : public Figure {

	int x{}, y{};

public:
	Point() = default;
	Point(const Point& p);
	Point(int x_, int y_, bool b_touch_, int width_, QColor color_);
	Point(int x_, int y_);

	void Move(PointT delta) override;
	std::vector<std::shared_ptr<Prim::Figure>> DecomposeFigure() const override;
	PointT GetCenter() const override ;
	PointT GetMaxXY() const override;
	bool IsBelongs(PointT point_) const override;
	void MoveAngle(double angle) override {};
	int IsMarkerHit(PointT point_) const override { return -1; }; //у точки нет маркеров
	bool MoveMarker(int markerIdx, PointT delta) override { return false; }; //у точки нет маркеров 
	std::shared_ptr<Figure> CreateCopy() const override;
	
	int GetX() const { return x; };
	int GetY() const { return y; };
	void SetX(int x_) { x = x_; };
	void SetY(int y_) { y = y_; };
	void SetEnd(PointT p) override { x = p.first; y = p.second; };
	void PointMoveAngle(const PointT& point_, double angle);

	
};