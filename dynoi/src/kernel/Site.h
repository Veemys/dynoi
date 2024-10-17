#pragma once

#include "Vector2D.h"

class Site
{
private:
	Vector2D coord_;

public:
	Site();
	Site(const Vector2D& v);
	Site(double x, double y);
	Site(const Site& other);

	~Site() {}

	const Vector2D& coord() const;
	double x() const;
	double y() const;

};