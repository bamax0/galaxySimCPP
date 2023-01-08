#include <iostream>
#include "initStar.h"
#include "barnes_hut.h"

int main()
{
    double dt = 0.01;
    double T = 40;
    int nb_star = 50000;
    star* galaxy = new star[nb_star];
    initStarCircle(galaxy, nb_star, dt);
    //initStarDoubleGalaxy(galaxy, nb_star, dt);
    //initStarUniverse(galaxy, nb_star, dt);
    integrate(galaxy, nb_star, dt, T);
    delete[] galaxy;
    return 0;
}