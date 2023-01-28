#ifndef STAR_H
#define STAR_H
#include "point.h"

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
