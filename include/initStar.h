#ifndef INITSTAR_H
#define INITSTAR_H
#include <math.h>
#include <iostream>
#include "star.h"
#include "galaxy.h"

#define PI 3.14159265358
void initSphereGalaxy(Galaxy &tab_star, const double dt);

void initStarCircle(Galaxy &tab_star, const double dt);

void initStarUniverse(Galaxy &tab_star, const double dt);

void initStarPlummer(Galaxy &tab_star, const double scale_length);

#endif