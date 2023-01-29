#include "galaxy.h"
#include <stdexcept>
#include <iostream>
// SingleGalaxy
SingleGalaxy::SingleGalaxy(const int &n)
{
    nb_star = n;
    star = new Star3d[n];
}

SingleGalaxy::~SingleGalaxy()
{
    delete[] star;
}

int SingleGalaxy::getNbStar() const
{
    return nb_star;
}

Star3d &SingleGalaxy::operator[](const int &i)
{
    if ((i < 0) || (nb_star <= i))
    {
        std::cout << nb_star << std::endl;
        std::cout << i << std::endl;
        throw std::invalid_argument("Index out of range");
    }
    return star[i];
}

// GalaxyUnion
GalaxyUnion::GalaxyUnion(Galaxy &g1, Galaxy &g2) : galaxy1(g1), galaxy2(g2)
{
}

GalaxyUnion::~GalaxyUnion()
{
}

int GalaxyUnion::getNbStar() const
{
    return galaxy1.getNbStar() + galaxy2.getNbStar();
}

Star3d &GalaxyUnion::operator[](const int &i)
{
    if ((i < 0) || (getNbStar() <= i))
    {
        throw std::invalid_argument("Index out of range");
    }

    if (i < galaxy1.getNbStar())
    {
        return galaxy1[i];
    }

    return galaxy2[i - galaxy1.getNbStar()];
}