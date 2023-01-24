#ifndef UTIL_H
#define UTIL_H

#include "star.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>

void saveMass(Star3d *stars, int nb_star);

void saveStar(Star3d *stars, int nb_star);

double invsqrtQuake(double number);

#endif