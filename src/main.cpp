#include <iostream>
#include "initStar.h"
#include "barnes_hut.h"

int main()
{
    double dt = 0.01;
    double T = 10;
    int nb_star = 100000;
    star *galaxy = new star[nb_star];
    // initStarCircle(galaxy, nb_star, dt);
    // initStarDoubleGalaxy(galaxy, nb_star, dt);
    // initStarUniverse(galaxy, nb_star, dt);
    initSphereGalaxy(galaxy, nb_star, dt);
    std::cout << "Galaxy generetion completed" << std::endl;
    integrate(galaxy, nb_star, dt, T);
    delete[] galaxy;
    return 0;
}