#include "initStar.h"
#include "util.h"
#include <cmath>
#include <random>

using namespace std;

void initSphereGalaxy(Star3d *tab_star, int nb_star, double dt)
{
    double r, phi, theta;
    double v_theta, v_phi, v_r;
    int i;
    double galaxyRadius = 4.0;
    double galaxy_velocity = 0.2;

    srand(time(NULL));

    for (i = 0; i < nb_star; i++)
    {
        theta = 2 * M_PI * getRandomValue();
        phi = acos(2 * getRandomValue() - 1);
        r = getRandomValueBetween(0.1, galaxyRadius);
        // calculate the position of the star
        tab_star[i].pos.x = r * sin(phi) * cos(theta);
        tab_star[i].pos.y = r * sin(phi) * sin(theta);
        tab_star[i].pos.z = r * cos(phi);
        tab_star[i].mass = (double)getRandomValueBetween(0.1, 10) / nb_star;

        v_theta = 2 * M_PI * getRandomValue();
        v_phi = acos(2 * getRandomValue() - 1);
        v_r = getRandomValueBetween(0, galaxy_velocity);

        tab_star[i].v.x = v_r / r * tab_star[i].pos.y;
        tab_star[i].v.y = v_r / r * tab_star[i].pos.x;
        tab_star[i].v.z = 0;

        tab_star[i].a.x = 0;
        tab_star[i].a.y = 0;
        tab_star[i].a.z = 0;
    }
}

void initStarCircle(Star3d *tab_star, int nb_star, double dt)
{
    double r, theta;
    double i, u;
    double pi = 3.14159265358;
    for (int j = 0; j < nb_star; j++)
    {
        i = j + .05;
        r = 3 * sqrt((double)i / nb_star);
        theta = pi * (1 + sqrt(5)) * i;

        tab_star[j].pos.x = r * cos(theta);
        tab_star[j].pos.y = r * sin(theta);
        tab_star[j].pos.y = 0;

        tab_star[j].v.x = -0.5 / r * sin(theta);
        tab_star[j].v.y = 0.5 / r * cos(theta);
        tab_star[j].v.z = 0;

        u = 4 * getRandomValue() + 0.2;
        tab_star[j].mass = (double)u / nb_star;
        tab_star[j].a.x = 0;
        tab_star[j].a.y = 0;
        tab_star[j].a.z = 0;
    }

    tab_star[0].mass = (double)10000. / nb_star;

    tab_star[nb_star / 5].mass = (double)300. / nb_star;
    tab_star[nb_star / 2].mass = (double)300. / nb_star;
    tab_star[nb_star - 10].mass = (double)300. / nb_star;
}

void initStarUniverse(Star3d *tab_star, int nb_star, double dt)
{
    float size = 2;
    float speed = 0.1;
    for (int j = 0; j < nb_star; j++)
    {

        tab_star[j].pos.x = getRandomValueBetween(-size, size);
        tab_star[j].pos.y = getRandomValueBetween(-size, size);
        tab_star[j].pos.z = getRandomValueBetween(-0.2, 0.2);

        tab_star[j].mass = (double)getRandomValueBetween(0.2, 7) / nb_star;

        tab_star[j].v.x = getRandomValueBetween(-speed, speed);
        tab_star[j].v.y = getRandomValueBetween(-speed, speed);
        tab_star[j].v.z = getRandomValueBetween(-speed, speed);

        tab_star[j].a.x = 0;
        tab_star[j].a.y = 0;
        tab_star[j].a.z = 0;
        if (getRandomValueBetween(0, 1000) < 1)
            tab_star[j].mass = getRandomValueBetween(15, 1000) / nb_star;
    }
}

void initStarPlummer(Star3d *galaxy, int nb_star, double scale_length)
{

    int N = nb_star;         // number of stars
    double M = 1.0;          // total mass of the galaxy
    double R = 3.0;          // scale radius of the galaxy
    double V = 1.0;          // scale velocity of the galaxy
    double flattening = 0.2; // flattening of the galaxy

    // Initialize the positions and velocities of the stars
    for (int i = 0; i < N; i++)
    {
        double r = R * pow(pow(getRandomValue(), -2.0 / 3.0) - 1.0, -1.0 / 2.0);
        double phi = 2 * M_PI * getRandomValue();
        double theta = acos(2 * getRandomValue() - 1);
        double z = r * flattening * cos(theta);
        double x = r * sqrt(1 - flattening * flattening) * cos(phi);
        double y = r * sqrt(1 - flattening * flattening) * sin(phi);
        double v = V * pow(r, 0.5);
        double v_phi = v * sqrt(1 - flattening * flattening) / r;
        double v_z = v * flattening * cos(theta) / r;
        galaxy[i].pos.x = x;
        galaxy[i].pos.y = y;
        galaxy[i].pos.z = z;

        galaxy[i].v.x = -v_phi * sin(phi);
        galaxy[i].v.y = v_phi * cos(phi);
        galaxy[i].v.z = v_z;

        galaxy[i].mass = M / N;

        galaxy[i].a.x = 0.0;
        galaxy[i].a.y = 0.0;
        galaxy[i].a.z = 0.0;
    }
}
