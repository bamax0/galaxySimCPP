#ifndef UTIL_H
#define UTIL_H

#include "star.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include "galaxy.h"

void saveMass(Galaxy &stars);

void saveStar(Galaxy &stars, int cpt);

double invsqrtQuake(double number);

double getRandomValue();

double getRandomValueBetween(double start, double end);

#endif