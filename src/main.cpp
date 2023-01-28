#include <iostream>
#include "initStar.h"
#include "barnes_hut.h"
using namespace std;

void integrate(Star3d *galaxy, int &nb_star, double &dt, double &T)
{
    double dt_2 = dt / 2;
    int cptCapt = 4;
    int cpt = 0;
    Point3d *force = new Point3d();
    Point3d partricles_force[nb_star];

    time_t begin = time(NULL);
    Star3d *s;
    int minute;
    saveMass(galaxy, nb_star);

    cout << "start" << endl;
    for (double t = 0; t < T; t += dt)
    {
        Node *root = new Node;
        root->bbox = find_root_bbox(galaxy, nb_star);
        for (int i = 0; i < nb_star; ++i)
        {
            s = &galaxy[i];
            quad_insert(root, s->pos, s->mass);
        }

        // #pragma omp parallel for
        for (int i = 0; i < nb_star; ++i)
        {
            s = &galaxy[i];
            compute_force(root, s->pos, s->mass, force);
            partricles_force[i] = *force;
        }

        for (int i = 0; i < nb_star; ++i)
        {
            Star3d *s = &galaxy[i];

            s->v += s->a * dt_2;

            s->a = partricles_force[i] / s->mass;

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
            saveStar(galaxy, nb_star);
        }
        ++cpt;
        delete root;
    }
    delete force;
}

int main()
{
    double dt = 0.01;
    double T = 10;
    int nb_star = 100000;
    Star3d *galaxy = new Star3d[nb_star];
    // initStarCircle(galaxy, nb_star, dt);
    // initStarDoubleGalaxy(galaxy, nb_star, dt);
    // initStarUniverse(galaxy, nb_star, dt);
    initSphereGalaxy(galaxy, nb_star, dt);
    cout << "Galaxy generetion completed" << endl;
    integrate(galaxy, nb_star, dt, T);
    delete[] galaxy;
    return 0;
}