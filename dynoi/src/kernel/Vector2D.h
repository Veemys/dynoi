#pragma once

class Vector2D
{
private:
	double x_;
	double y_;

public:
	Vector2D();
	Vector2D(double x, double y);
	Vector2D(const Vector2D& other);
	void operator=(const Vector2D& other);

	~Vector2D() {}

	const double& x() const;
	const double& y() const;

	double& x();
	double& y();
	
	friend Vector2D operator+(const Vector2D& a, const Vector2D& b);
	friend Vector2D operator-(const Vector2D& a, const Vector2D& b);
	friend double operator*(const Vector2D& a, const Vector2D& b);
	friend Vector2D operator*(const Vector2D& v, const double a);
	friend Vector2D operator*(const double a, const Vector2D& v);
	friend Vector2D operator/(const Vector2D& v, const double a);

	double length() const;
	Vector2D getNorm() const;
	void normalize();
	Vector2D getReverse() const;
	void reverse();

};