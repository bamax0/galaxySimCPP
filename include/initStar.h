#ifndef INITSTAR_H
#define INITSTAR_H
#include <math.h>
#include <iostream>
#include "star.h"
#include "galaxy.h"

#define PI 3.14159265358

void initStarUniverse(Galaxy &tab_star, const double dt);

void initGalaxy(Galaxy &galaxy, double dt);

#endif