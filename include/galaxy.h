#ifndef GALAXY_H
#define GALAXY_H

#include "star.h"
class Galaxy
{
public:
    virtual int getNbStar() const = 0;
    virtual Star3d &operator[](const int &i) = 0;
};

class SingleGalaxy : public Galaxy
{
private:
    Star3d *star;
    int nb_star;

public:
    SingleGalaxy(const int &nb_star);
    ~SingleGalaxy();
    int getNbStar() const;
    Star3d &operator[](const int &i);
};

class GalaxyUnion : public Galaxy
{
private:
    Galaxy &galaxy1;
    Galaxy &galaxy2;

public:
    GalaxyUnion(Galaxy &g1, Galaxy &g2);
    ~GalaxyUnion();
    int getNbStar() const;
    Star3d &operator[](const int &i);
};

#endif