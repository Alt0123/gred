#pragma once

#include <QPainter>

//Классы векторных примитивов

namespace Prim
{
	class Figure
	{
	public:
		virtual void Draw(QPainter&) const = 0;
	};


	class Point : public Figure
	{
	private:
		int x{}, y{};

	public:
		Point() = default;

		Point(int, int);

		void Draw(QPainter&) const override;

		int GetX() const { return x; };

		int GetY() const { return y; };
	};


	class Line : public Figure
	{
	private:
		Point start{}, end{};

	public:
		Line() = default;

		Line(Point, Point);

		void Draw(QPainter&) const override;

		Point GetStart() const { return start; }

		Point GetEnd() const { return end; }
	};


	class Ellipse : public Figure
	{
	private:
		Point center{};
		int a{}, b{};
		int m_angle;

	public:
		Ellipse() = default;

		Ellipse(Point center, int a, int b, int angle);

		void Draw(QPainter&) const override;

		Point GetCenter() const { return center; }

		int GetA() const { return a; }

		int GetB() const { return b; }
	};
}