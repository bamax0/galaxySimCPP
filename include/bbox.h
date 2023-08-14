#ifndef BBOX_H
#define BBOX_H
#include "point.h"


class Bbox
{
public:
    Point3d p;
    double size; // cube bbox
    Bbox(const double& x, const double& y, const double& z, const double size) : p(x, y, z), size(size){}
    Bbox(const Point3d& p, const double size) : p(p), size(size){}
};

#endif