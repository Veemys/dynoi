#pragma once

#include "Figure.h"
#include "../kernel/Vector2D.h"

class Triangle : public Figure
{
private:
	Vector2D a_;
	Vector2D b_;
	Vector2D c_;

public:
	Triangle(const Vector2D& a, const Vector2D& b, const Vector2D& c);

	const Vector2D& a() const;
	const Vector2D& b() const;
	const Vector2D& c() const;

	double area() const override final;
	double perimeter() const override final;

};