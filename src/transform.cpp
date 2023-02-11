#include "transform.h"
#include <cmath>

Point3d degreeToradian(const Point3d &angle)
{
    return angle * M_PI / 180;
}

Point3d rotateX(const Point3d &point, const double &angle)
{
    Point3d rotated;
    rotated.x = point.x;
    rotated.y = point.y * cos(angle) - point.z * sin(angle);
    rotated.z = point.y * sin(angle) + point.z * cos(angle);
    return rotated;
}
Point3d rotateY(const Point3d &point, const double &angle)
{
    Point3d rotated;
    rotated.x = point.x * cos(angle) + point.z * sin(angle);
    rotated.y = point.y;
    rotated.z = -point.x * sin(angle) + point.z * cos(angle);
    return rotated;
}

Point3d rotateZ(const Point3d &point, const double &angle)
{
    Point3d rotated;
    rotated.x = point.x * cos(angle) - point.y * sin(angle);
    rotated.y = point.x * sin(angle) + point.y * cos(angle);
    rotated.z = point.z;
    return rotated;
}
Point3d rotate(const Point3d &point, const Point3d &angle)
{
    Point3d rotated;
    rotated = rotateX(point, angle.x);
    rotated = rotateY(rotated, angle.y);
    rotated = rotateZ(rotated, angle.z);
    return rotated;
}

void rotateGalaxy(Galaxy &galaxy, const Point3d &angle)
{
    for (int i = 0; i < galaxy.getNbStar(); i++)
    {
        galaxy[i].pos = rotate(galaxy[i].pos, angle);

        galaxy[i].v = rotate(galaxy[i].v, angle);
    }
}

void moveGalaxy(Galaxy &galaxy, const Point3d &mov)
{
    for (int i = 0; i < galaxy.getNbStar(); i++)
    {
        galaxy[i].pos += mov;
    }
}