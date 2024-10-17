#include "Triangle.h"

#include <cmath>

Triangle::Triangle(const Vector2D& a, const Vector2D& b, const Vector2D& c)
	: a_(a), b_(b), c_(c)
{

}

const Vector2D& Triangle::a() const
{
	return a_;
}

const Vector2D& Triangle::b() const
{
	return b_;
}

const Vector2D& Triangle::c() const
{
	return c_;
}

double Triangle::area() const
{
	Vector2D A(b_ - a_);
	Vector2D B(c_ - a_);
	return 0.5 * std::abs(A.x() * B.y() - A.y() * B.x());
}

double Triangle::perimeter() const
{
	double A = (b_ - a_).length();
	double B = (c_ - a_).length();
	double C = (c_ - b_).length();
	return (A + B + C);
}