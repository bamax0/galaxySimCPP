#ifndef BBOX_H
#define BBOX_H

class Bbox
{
public:
    Point3d p;
    double size; // cube bbox
    Bbox(const double& x, const double& y, const double& z, const double size) : p(x, y, z), size(size){}
};

#endif