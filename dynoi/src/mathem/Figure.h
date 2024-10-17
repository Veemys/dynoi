#pragma once

class Figure abstract
{
public:
	virtual double area() const = 0;
	virtual double perimeter() const = 0;
};