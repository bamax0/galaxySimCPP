#include "bbox.h"

Bbox *Bbox::get_quadrant(const int &quadrant) const
{
    Bbox *b = new Bbox();
    double x = (x1 + x2) / 2.;
    double y = (y1 + y2) / 2.;
    double z = (z1 + z2) / 2.;
    // Quadrant 0: (xmin, x, y, ymax)
    switch (quadrant)
    {
    case 0:
        b->x1 = x1;
        b->y1 = y;
        b->z1 = z;

        b->x2 = x;
        b->y2 = y2;
        b->z2 = z2;
        break;
    case 1:
        b->x1 = x;
        b->y2 = y2;
        b->z2 = z2;

        b->x2 = x2;
        b->y1 = y;
        b->z1 = z;
        break;
    case 2:
        b->x2 = x2;
        b->y2 = y;
        b->z2 = z2;

        b->x1 = x;
        b->y1 = y1;
        b->z1 = z;
        break;
    case 3:
        b->x1 = x1;
        b->y1 = y1;
        b->z1 = z;

        b->x2 = x;
        b->z2 = z2;
        b->y2 = y;

        break;

    case 4:
        b->x1 = x1;
        b->y1 = y;
        b->z1 = z1;

        b->x2 = x;
        b->y2 = y2;
        b->z2 = z;
        break;
    case 5:
        b->x2 = x2;
        b->y2 = y2;
        b->z2 = z;

        b->x1 = x;
        b->y1 = y;
        b->z1 = z1;
        break;
    case 6:
        b->x1 = x;
        b->y1 = y1;
        b->z1 = z1;

        b->x2 = x2;
        b->y2 = y;
        b->z2 = z;
        break;
    case 7:
        b->x1 = x1;
        b->y1 = y1;
        b->z1 = z1;

        b->x2 = x;
        b->y2 = y;
        b->z2 = z;
        break;
    }
    return b;
}