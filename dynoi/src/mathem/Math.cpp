#include "Math.h"

#include <cfloat>
#include <limits>
#include <cmath>

#include "../kernel/Vector2D.h"
#include "Triangle.h"

const double Math::eps = 1e-10;

Vector2D Math::straightsIntersection(const std::pair<Vector2D, Vector2D>& oneStraight, const std::pair<Vector2D, Vector2D>& twoStraight)
{
    double a1 = oneStraight.second.y() - oneStraight.first.y();
    double b1 = oneStraight.first.x() - oneStraight.second.x();
    double c1 = -oneStraight.first.x() * oneStraight.second.y() + oneStraight.first.y() * oneStraight.second.x();

    double a2 = twoStraight.second.y() - twoStraight.first.y();
    double b2 = twoStraight.first.x() - twoStraight.second.x();
    double c2 = -twoStraight.first.x() * twoStraight.second.y() + twoStraight.first.y() * twoStraight.second.x();

    double A = (b1 * c2 - b2 * c1);
    double B = (a2 * c1 - a1 * c2);
    double C = (a1 * b2 - a2 * b1);

    if (C == 0.0)
    {
        return Vector2D(std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
    }

    return Vector2D(A / C, B / C);
}

bool Math::pointLayInsideTriangle(const Vector2D& point, const Triangle& triangle)
{
    Triangle littleTriangle1(triangle.a(), triangle.b(), point);
    Triangle littleTriangle2(triangle.a(), triangle.c(), point);
    Triangle littleTriangle3(triangle.b(), triangle.c(), point);
    double summedArea = littleTriangle1.area() + littleTriangle2.area() + littleTriangle3.area();

    return (std::abs(summedArea - triangle.area()) < eps);
}

bool Math::pointLayInsideSegment(const Vector2D& point, const std::pair<Vector2D, Vector2D>& segment)
{
    double fromStartToPointDistance = (point - segment.first).length();
    double fromEndToPointDistance = (point - segment.second).length();
    double segmentLength = (segment.second - segment.first).length();

    return (std::abs((fromStartToPointDistance + fromEndToPointDistance) - segmentLength) < eps);
}

bool Math::isTheSamePoints(const Vector2D& firstPoints, const Vector2D& secondPoints)
{
    return ((firstPoints - secondPoints).length() < eps);
}

bool Math::pointsLayFromOneSide(const Vector2D& firstPoint, const Vector2D& secondPoint, const std::pair<Vector2D, Vector2D>& straight)
{
    Vector2D straightDirection = (straight.second - straight.first).getNorm();
    Vector2D fromStraightStartToFirstPoint = (firstPoint - straight.first).getNorm();
    Vector2D fromStraightStartToSecondPoint = (secondPoint - straight.first).getNorm();

    double A = (straightDirection.x() * fromStraightStartToFirstPoint.y() - straightDirection.y() * fromStraightStartToFirstPoint.x());
    double B = (straightDirection.x() * fromStraightStartToSecondPoint.y() - straightDirection.y() * fromStraightStartToSecondPoint.x());
    return (A * B > 0);
}