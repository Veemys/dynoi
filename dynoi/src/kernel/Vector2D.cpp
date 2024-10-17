#include "Vector2D.h"

#include <cmath>

Vector2D::Vector2D()
	: x_(0.0), y_(0.0)
{

}

Vector2D::Vector2D(double x, double y)
	: x_(x), y_(y)
{

}

Vector2D::Vector2D(const Vector2D& other)
	: x_(other.x_), y_(other.y_)
{

}

void Vector2D::operator=(const Vector2D& other)
{
	x_ = other.x_;
	y_ = other.y_;
}

double Vector2D::x() const
{
	return x_;
}

double Vector2D::y() const
{
	return y_;
}

double& Vector2D::x()
{
	return x_;
}

double& Vector2D::y()
{
	return y_;
}

double Vector2D::length()
{
	return std::sqrt(x_ * x_ + y_ * y_);
}

Vector2D Vector2D::getNorm()
{
	return Vector2D(x_ / length(), y_ / length());
}

void Vector2D::normalize()
{
	double l = length();
	x_ /= l;
	y_ /= l;
}

Vector2D Vector2D::getReverse()
{
	return (*this) * -1;
}

void Vector2D::reverse()
{
	x_ *= -1;
	y_ *= -1;
}

Vector2D operator+(const Vector2D& a, const Vector2D& b)
{
	return Vector2D(a.x_ + b.x_, a.y_ + b.y_);
}

Vector2D operator-(const Vector2D& a, const Vector2D& b)
{
	return Vector2D(a.x_ - b.x_, a.y_ - b.y_);
}

double operator*(const Vector2D& a, const Vector2D& b)
{
	return (a.x_ * b.x_ + a.y_ * b.y_);
}

Vector2D operator*(const Vector2D& v, const double a)
{
	return Vector2D(a * v.x_, a * v.y_);
}

Vector2D operator*(const double a, const Vector2D& v)
{
	return v * a;
}

Vector2D operator/(const Vector2D& v, const double a)
{
	return Vector2D(v.x_ / a, v.y_ / a);
}