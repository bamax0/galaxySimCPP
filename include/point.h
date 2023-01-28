#ifndef POINT_H
#define POINT_H

class Point3d
{
public:
    double x, y, z;

public:
    Point3d() : x(0), y(0), z(0) {}
    Point3d(const double &x, const double &y, const double &z) : x(x), y(y), z(z) {}
    Point3d(const Point3d &p) : x(p.x), y(p.y), z(p.z) {}

    Point3d &operator=(const Point3d &p);
    Point3d &operator+=(const Point3d &p);
    bool operator==(const Point3d &p) const;
    Point3d operator+(const Point3d &p) const;
    Point3d operator*(const double &a) const;
    Point3d operator/(const double &a) const;

    double max() const;
    void setPoint(const double &xc, const double &yc, const double &zc);
    bool isNull() const;
};

Point3d operator-(const double &a, const Point3d &p);

#endif