#include "initStar.h"
#include "util.h"
#include <cmath>
#include <random>

using namespace std;

void initSphereGalaxy(Galaxy &galaxy, const double dt)
{
    double r, phi, theta;
    double v_theta, v_phi, v_r;
    int i;
    double galaxyRadius = 4.0;
    double galaxy_velocity = 0.2;

    srand(time(NULL));

    for (i = 0; i < galaxy.getNbStar(); i++)
    {
        theta = 2 * M_PI * getRandomValue();
        phi = acos(2 * getRandomValue() - 1);
        r = getRandomValueBetween(0.1, galaxyRadius);
        // calculate the position of the star
        galaxy[i].pos.x = r * sin(phi) * cos(theta);
        galaxy[i].pos.y = r * sin(phi) * sin(theta);
        galaxy[i].pos.z = r * cos(phi);
        galaxy[i].mass = (double)getRandomValueBetween(0.1, 10) / galaxy.getNbStar();

        v_theta = 2 * M_PI * getRandomValue();
        v_phi = acos(2 * getRandomValue() - 1);
        v_r = getRandomValueBetween(-galaxy_velocity, galaxy_velocity);

        galaxy[i].v.x = getRandomValueBetween(-galaxy_velocity, galaxy_velocity); // v_r / r * galaxy[i].pos.y;
        galaxy[i].v.y = getRandomValueBetween(-galaxy_velocity, galaxy_velocity); // v_r / r * galaxy[i].pos.x;
        galaxy[i].v.z = getRandomValueBetween(-galaxy_velocity, galaxy_velocity);

        galaxy[i].a.x = 0;
        galaxy[i].a.y = 0;
        galaxy[i].a.z = 0;
    }
}

void initStarCircle(Galaxy &galaxy, const double dt)
{
    double r, theta;
    double i, u;
    double pi = 3.14159265358;
    for (int j = 0; j < galaxy.getNbStar(); j++)
    {
        i = j + .05;
        r = 3 * sqrt((double)i / galaxy.getNbStar());
        theta = pi * (1 + sqrt(5)) * i;

        galaxy[j].pos.x = r * cos(theta);
        galaxy[j].pos.y = r * sin(theta);
        galaxy[j].pos.y = 0;

        galaxy[j].v.x = -0.5 / r * sin(theta);
        galaxy[j].v.y = 0.5 / r * cos(theta);
        galaxy[j].v.z = 0;

        u = 4 * getRandomValue() + 0.2;
        galaxy[j].mass = (double)u / galaxy.getNbStar();
        galaxy[j].a.x = 0;
        galaxy[j].a.y = 0;
        galaxy[j].a.z = 0;
    }

    galaxy[0].mass = (double)10000. / galaxy.getNbStar();

    galaxy[galaxy.getNbStar() / 5].mass = (double)300. / galaxy.getNbStar();
    galaxy[galaxy.getNbStar() / 2].mass = (double)300. / galaxy.getNbStar();
    galaxy[galaxy.getNbStar() - 10].mass = (double)300. / galaxy.getNbStar();
}

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

void initStarPlummer(Galaxy &galaxy, const double scale_length)
{

    int N = galaxy.getNbStar(); // number of stars
    double M = 1.0;             // total mass of the galaxy
    double R = 3.0;             // scale radius of the galaxy
    double V = 1.0;             // scale velocity of the galaxy
    double flattening = 0.2;    // flattening of the galaxy

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
