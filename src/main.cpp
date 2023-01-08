#include <iostream>
#include "initStar.h"
#include "barnes_hut.h"

int main()
{
    double dt = 0.03;
    double T = 60;
    int nb_star = 700000;
    star* galaxy = new star[nb_star];
    //initStarCircle(galaxy, nb_star, dt);
    initStarDoubleGalaxy(galaxy, nb_star, dt);
    integrate(galaxy, nb_star, dt, T);
    delete[] galaxy;
    return 0;
}