#pragma once

#include <utility>

class Vector2D;
class Triangle;

class Math
{
public:
    static const double eps;

    static Vector2D straightsIntersection(const std::pair<Vector2D, Vector2D>& oneStraight, const std::pair<Vector2D, Vector2D>& twoStraight);
    static bool pointLayInsideTriangle(const Vector2D& point, const Triangle& triangle);
    static bool pointLayInsideSegment(const Vector2D& point, const std::pair<Vector2D, Vector2D>& segment);
    static bool isTheSamePoints(const Vector2D& firstPoints, const Vector2D& secondPoints);
    static bool pointsLayFromOneSide(const Vector2D& firstPoint, const Vector2D& secondPoint, const std::pair<Vector2D, Vector2D>& straight);

};