#ifndef STAR_H
#define STAR_H

typedef struct star
{
    double x, y, z;

    double vx, vy, vz;

    double ax, ay, az;

    double mass;
} star;

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
    Point3d &operator*=(const double &a);
    bool operator==(const Point3d &p) const;
    Point3d operator+(const Point3d &p) const;
    Point3d operator*(const double &a) const;
    Point3d operator+(const double &a) const;
    Point3d operator/(const double &a) const;

    double max() const;
    void setPoint(const double &xc, const double &yc, const double &zc);
    bool isNull() const;
};

Point3d operator-(const double &a, const Point3d &p);

class Star3d
{
public:
    Point3d pos;

    Point3d v;

    Point3d a;

    double mass;

    Star3d(const Point3d &pos, const Point3d &v, const Point3d a, const double &mass) : pos(pos), v(v), a(a), mass(mass) {}

    Star3d() : pos(), v(), a(), mass() {}
    Star3d(const Star3d &s) : pos(s.pos), v(s.v), a(s.a), mass(s.mass) {}

    Star3d &operator=(const Star3d &s);
};

#endif // STAR_H
