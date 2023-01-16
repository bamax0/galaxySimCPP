#ifndef INITSTAR_H
#define INITSTAR
#include <math.h>
#include <iostream>
#include "star.h"

#define PI 3.14159265358
void initSphereGalaxy(star* tab_star, int nb_star, double dt);

void initStarCircle(star* tab_star, int nb_star, double dt);

void initStarUniverse(star* tab_star, int nb_star, double dt);

void initStarPlummer(star* tab_star, int nb_star, double scale_length);

#endif