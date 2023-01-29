#ifndef BBOX_H
#define BBOX_H

class Bbox
{
public:
    double x1, y1, z1;
    double x2, y2, z2;
    Bbox *get_quadrant(const int &quadrant) const;
};

#endif