#include "Site.h"

#include "Vector2D.h"

Site::Site()
	: coord_()
{

}

Site::Site(const Vector2D& v)
	: coord_(v)
{

}

Site::Site(double x, double y)
	: coord_(x, y)
{

}

Site::Site(const Site& other)
	: coord_(other.coord_)
{

}

const Vector2D& Site::coord() const
{
	return coord_;
}

double Site::x() const
{
	return coord_.x();
}

double Site::y() const
{
	return coord_.y();
}