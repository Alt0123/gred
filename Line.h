#pragma once
#include "Figure.h"
#include "Point.h"

class Line : public Figure {

Point start, end;

public:
	Line();
	Line(const Line& l);
	Line(const Point& start_, const Point& end_, bool b_touch_, int width_, QColor color_);
	Line(const Point& start_, const Point& end_);

	void Move(PointT delta) override;
	std::vector<std::shared_ptr<Prim::Figure>> DecomposeFigure() const override;
	PointT GetCenter() const override;
	PointT GetMaxXY() const override;
	bool IsBelongs(PointT point_) const override;
	void MoveAngle(double angle) override;
	int IsMarkerHit(PointT point_) const override;
	bool MoveMarker(int markerIdx, PointT delta) override;
	std::shared_ptr<Figure> CreateCopy() const override;

	Point GetStart() const { return start; };
	Point GetEnd() const { return end; };
	void SetStart(const Point& start_) { start = start_; };
	void SetEnd(const Point& end_) { end = end_; };
	void SetEnd(PointT p) override { end = Point(p.first, p.second); };
	/// Поворот линии относительно любой точки
	void LineMoveAngle(const PointT& point_, double angle);
	int Length() const;

};