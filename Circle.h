#pragma once
#include "Figure.h"
#include "Point.h"
#include "Line.h"

class Circle : public Figure {

	Point centre;
	int radius;

public:
	Circle();
	Circle(const Circle& c);
	Circle(const Point& centre_, int radius_, bool b_touch_, int width_, QColor color_);
	Circle(const Point& centre_, int radius_);

	void Move(PointT delta) override { centre.Move(delta); };
	std::vector<std::shared_ptr<Prim::Figure>> DecomposeFigure() const override;
	PointT GetCenter() const override { return PointT(centre.GetX(), centre.GetY()); };
	PointT GetMaxXY() const override;
	bool IsBelongs(PointT point_) const override;
	void MoveAngle(double angle) override {};
	void SetEnd(PointT p) override;
	int IsMarkerHit(PointT pnt) const override { return -1; }; //заглушка, т.к. реализация нужна лишь для класса line
	bool MoveMarker(int markerIdx, PointT delta) override { return false; }; //заглушка, т.к. реализация нужна лишь для класса line
	std::shared_ptr<Figure> CreateCopy() const override;

	Point GetCentre() const { return centre; };
	int GetRadius() const { return radius; };
	void SetCentre(const Point& centre_) { centre = centre_; };
	void SetRadius(int radius_) { radius = radius_; }

};
