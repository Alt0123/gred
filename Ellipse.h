#pragma once
#include "Figure.h"
#include "Line.h"

class Ellipse_ : public Figure {

	Point centre;
	int a, b;
	/// Угол поворота
	double m_angle; 

public:
	Ellipse_() = default;
	Ellipse_(const Ellipse_& el);
	Ellipse_(const Point& centre_, int a_, int b_, double angle_, bool b_touch_, int width_, QColor color_);
	Ellipse_(const Point& centre_, int a_, int b_, double angle_);
	Ellipse_(const Point& centre_, int a_, int b_);

	void Move(PointT delta) override { centre.Move(delta); };
	std::vector<std::shared_ptr<Prim::Figure>> DecomposeFigure() const override;
	PointT GetCenter() const override { return PointT(centre.GetX(), centre.GetY()); };
	PointT GetMaxXY() const override;
	bool IsBelongs(PointT point_) const override;
	void MoveAngle(double angle) override { m_angle += angle; };
	void SetEnd(PointT p) override {
		a = p.first - centre.GetX();
		b = p.second - centre.GetY();
	}
	int IsMarkerHit(PointT pnt) const override { return -1; }; //заглушка, т.к. реализация нужна лишь для класса line
	bool MoveMarker(int markerIdx, PointT delta) override { return false; }; //заглушка, т.к. реализация нужна лишь для класса line
	std::shared_ptr<Figure> CreateCopy() const override;

	Point GetCentre() const { return centre; };
	int Get_a() const { return a; };
	int Get_b() const { return b; };
	double GetAngle() const { return m_angle; };
	void SetCentre(const Point& centre_) { centre = centre_; };
	void Set_a(int a_) { a = a_; };
	void Set_b(int b_) { b = b_; };

};