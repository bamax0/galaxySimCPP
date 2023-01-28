#include "star.h"

Star3d &Star3d::operator=(const Star3d &s)
{
    pos = s.pos;
    v = s.v;
    a = s.a;
    mass = s.mass;
    return *this;
}