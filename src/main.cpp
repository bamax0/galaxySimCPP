#include <iostream>
#include "initStar.h"
#include "barnes_hut.h"
#include "transform.h"
#include "configurationParser.h"
#include <sstream>
using namespace std;

void integrate(Galaxy &galaxy, const double &dt, const double &T, const double &softening)
{
    double softeningSquare = softening * softening;
    double dt_2 = dt / 2;

    int cptCapt = 40;
    int cpt = 0;
    Point3d *force = new Point3d();

    time_t begin = time(NULL);
    int minute;
    saveMass(galaxy);

    cout << "start" << endl;
    for (double t = 0; t < T; t += dt)
    {
        Node *root = new Node;
        root->bbox = find_root_bbox(galaxy);
        for (int i = 0; i < galaxy.getNbStar(); ++i)
        {
            Star3d *s = &galaxy[i];
            quad_insert(root, s->pos, s->mass);
        }

#pragma omp parallel for
        for (int i = 0; i < galaxy.getNbStar(); ++i)
        {
            Star3d *s = &galaxy[i];
            compute_force(root, s->pos, s->mass, force, softeningSquare);

            s->v += s->a * dt_2;

            s->a = (*force) / s->mass;

            s->v += s->a * dt_2;

            s->pos += s->v * dt;
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
            saveStar(galaxy);
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

    cout << "Galaxy generetion completed" << endl;
    integrate(galaxy, dt, T, softening);
    return 0;
}