#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "galaxy.h"
#include "point.h"

Point3d degreeToRadian(const Point3d &angle);

void rotateGalaxy(Galaxy &galaxy, const Point3d &angle);
void moveGalaxy(Galaxy &galaxy, const Point3d &mov);

Point3d rotateZ(const Point3d &point, const double &angle);
Point3d rotateY(const Point3d &point, const double &angle);
Point3d rotateX(const Point3d &point, const double &angle);
Point3d rotate(const Point3d &point, const Point3d &angle);

#endif