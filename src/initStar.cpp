#include "initStar.h"
#include "util.h"
#include <cmath>
#include <random>

using namespace std;

void initStarUniverse(Galaxy &galaxy, double dt)
{
    float size = 2;
    float speed = 0.1;
    for (int j = 0; j < galaxy.getNbStar(); j++)
    {

        galaxy[j].pos.x = getRandomValueBetween(-size, size);
        galaxy[j].pos.y = getRandomValueBetween(-size, size);
        galaxy[j].pos.z = getRandomValueBetween(-0.2, 0.2);

        galaxy[j].mass = (double)getRandomValueBetween(0.2, 7) / galaxy.getNbStar();

        galaxy[j].v.x = getRandomValueBetween(-speed, speed);
        galaxy[j].v.y = getRandomValueBetween(-speed, speed);
        galaxy[j].v.z = getRandomValueBetween(-speed, speed);

        galaxy[j].a.x = 0;
        galaxy[j].a.y = 0;
        galaxy[j].a.z = 0;
        if (getRandomValueBetween(0, 1000) < 1)
            galaxy[j].mass = getRandomValueBetween(15, 1000) / galaxy.getNbStar();
    }
}

void initGalaxy(Galaxy &galaxy, double dt)
{
    double u, phi;
    int i;
    int nb_star = galaxy.getNbStar();
    double radius = 2;
    double v = 0.5;
    double r, v_rand;
    srand(time(NULL));
    for (i = 1; i < nb_star; i++)
    {
        phi = getRandomValueBetween(0, 2 * PI);
        r = pow(radius * getRandomValue(), 1. / 3);
        galaxy[i].pos.x = r * cos(phi);
        galaxy[i].pos.y = r * sin(phi);
        galaxy[i].pos.z = getRandomValueBetween(-0.01, 0.01);

        galaxy[i].mass = (double)getRandomValueBetween(0.05, 5) / galaxy.getNbStar();

        v_rand = (double)getRandomValueBetween(-v, v);
        galaxy[i].v.x = -v_rand * sin(phi) * dt;
        galaxy[i].v.y = v_rand * cos(phi) * dt;
        galaxy[i].v.z = 0;

        galaxy[i].a = Point3d();
    }

    // black hole generation
    galaxy[0].pos = Point3d();

    galaxy[0].mass = (double)getRandomValueBetween(100, 5000) / galaxy.getNbStar();

    galaxy[0].v = Point3d();
}
