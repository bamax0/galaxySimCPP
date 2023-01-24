#ifndef INITSTAR_H
#define INITSTAR
#include <math.h>
#include <iostream>
#include "star.h"

#define PI 3.14159265358
void initSphereGalaxy(Star3d *tab_star, int nb_star, double dt);

void initStarCircle(Star3d *tab_star, int nb_star, double dt);

void initStarUniverse(Star3d *tab_star, int nb_star, double dt);

void initStarPlummer(Star3d *tab_star, int nb_star, double scale_length);

#endif