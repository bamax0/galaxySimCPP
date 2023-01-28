#include "point.h"

Point3d &Point3d::operator=(const Point3d &p)
{
    setPoint(p.x, p.y, p.z);
    return *this;
}

Point3d &Point3d::operator+=(const Point3d &p)
{
    x += p.x;
    y += p.y;
    z += p.z;
    return *this;
}

Point3d Point3d::operator+(const Point3d &p) const
{
    return Point3d(x + p.x, y + p.y, z + p.z);
}

bool Point3d::operator==(const Point3d &p) const
{
    return (x == p.x) && (y == p.y) && (z == p.z);
}

Point3d Point3d::operator*(const double &a) const
{
    return Point3d(x * a, y * a, z * a);
}

double Point3d::max() const
{
    if (x > y)
    {
        if (x > z)
            return x;
        return z;
    }

    if (y > z)
        return y;
    return z;
}

void Point3d::setPoint(const double &xc, const double &yc, const double &zc)
{
    x = xc;
    y = yc;
    z = zc;
}

bool Point3d::isNull() const
{
    return (x == 0) && (y == 0) && (z == 0);
}

Point3d Point3d::operator/(const double &a) const
{
    return Point3d(x / a, y / a, z / a);
}
Point3d operator-(const double &a, const Point3d &p)
{
    return Point3d(a - p.x, a - p.y, a - p.z);
}