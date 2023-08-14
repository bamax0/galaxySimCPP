#include <iostream>
#include <sstream>
#include "initStar.h"
#include "transform.h"
#include "configurationParser.h"
#include "imageGenerator.h"
#include "octreeNode.h"
using namespace std;

void integrate(Galaxy &galaxy, const double &dt, const double &T, const double &softening, const int &cptCapt)
{
    double softeningSquare = softening * softening;
    double dt_2 = dt / 2;
    double expensionRate = 0.0184; // real 0.0384
    int cpt = 0;
    Point3d *force = new Point3d();

    time_t begin = time(NULL);
    int minute;
    saveMass(galaxy);

    cout << "start" << endl;
    for (double t = 0; t < T; t += dt)
    {
        OctreeNode *root = new OctreeNode(Bbox(0, 0, 0, 1));
        for (int i = 0; i < galaxy.getNbStar(); ++i)
        {
            Star3d *s = &galaxy[i];
            root->appendStar(s->pos, s->mass);
        }

#pragma omp parallel for
        for (int i = 0; i < galaxy.getNbStar(); ++i)
        {
            Star3d *s = &galaxy[i];

            s->v += s->a * dt_2;

            s->a = root->compute_force(s->pos, s->mass, softeningSquare) / s->mass;

            s->v += s->a * dt_2;

            s->pos += s->v * dt + s->pos * expensionRate * dt;
        }

        if (cpt % cptCapt == 0)
        {
            time_t end = time(NULL);
            if (t)
            {
                minute = (int)(end - begin) * (T / t - 1);
                cout << (int)(t / T * 10000) / 100. << "\% time left: "
                     << (int)(minute / 60 / 60) << "h " << (minute / 60) % 60
                     << "m (time :" << (int)(end - begin) / 60 << "m )" << endl;
            }
            saveStar(galaxy, cpt / cptCapt);
            generateImage(galaxy, cpt / cptCapt);
        }
        ++cpt;
        delete root;
    }
    delete force;
}

int main()
{
    ConfigurationParser c = ConfigurationParser("./config.txt");

    double softening = c.getValue<double>("softening");
    double T = c.getValue<double>("totalDuration");
    double dt = c.getValue<double>("timeStep");
    int nb_star = c.getValue<int>("nbStarPerGalaxy");
    int nb_frame = c.getValue<int>("NbFrame");
    int cptCapt = (int)(T / dt / nb_frame);
    if (cptCapt < 1)
        cptCapt = 2;

#if False
    SingleGalaxy galaxy1(nb_star);
    initGalaxy(galaxy1, dt);
    rotateGalaxy(galaxy1, degreeToRadian({45, 0, 0}));
    moveGalaxy(galaxy1, {2, 2, 2});

    SingleGalaxy galaxy2(nb_star);
    initGalaxy(galaxy2, dt);
    rotateGalaxy(galaxy2, degreeToRadian({0, 45, 0}));
    moveGalaxy(galaxy2, {-2, -2, -2});

    GalaxyUnion galaxyUnion1(galaxy1, galaxy2);

    SingleGalaxy galaxy3(nb_star);
    initGalaxy(galaxy3, dt);
    rotateGalaxy(galaxy3, degreeToRadian({0, 0, 45}));
    moveGalaxy(galaxy3, {2, -2, 2});

    SingleGalaxy galaxy4(nb_star);
    initGalaxy(galaxy4, dt);
    rotateGalaxy(galaxy4, degreeToRadian({-45, 45, 45}));
    moveGalaxy(galaxy4, {-2, 2, -2});

    GalaxyUnion galaxyUnion2(galaxy3, galaxy4);

    GalaxyUnion galaxy(galaxyUnion1, galaxyUnion2);
#else
    SingleGalaxy galaxy(nb_star);
    initStarUniverse(galaxy, dt);
#endif
    cout << "Galaxy generetion completed" << endl;
    integrate(galaxy, dt, T, softening, cptCapt);
    return 0;
}