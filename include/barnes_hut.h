#ifndef BARNES_HUT_H
#define BARNES_HUT_H
#include "star.h"
#include "util.h"

typedef struct bbox
{
    double x1, x2;
    double y1, y2;
    double z1, z2;
} Bbox;

class Node
{
public:
    Node *children[8];
    double mass;
    Point3d cm;
    Bbox *bbox;

    Node()
    {
        for (int k = 0; k < 8; ++k)
            children[k] = nullptr;

        mass = 0;

        cm.x = 0;
        cm.y = 0;
        cm.z = 0;
    }

    ~Node()
    {
        for (int k = 0; k < 8; ++k)
            delete children[k];

        delete bbox;
    }

    bool is_children_null()
    {
        for (int k = 0; k < 8; ++k)
        {
            if (children[k] != nullptr)
                return false;
        }
        return true;
    }
};
void integrate(Star3d *galaxy, int &nb_star, double &dt, double &T);
Bbox *find_root_bbox(Star3d *galaxy, int &nb_star);
void quad_insert(Node *root, double &x, double &y, double &z, double &m);
int quadrant_of_particle(Bbox *bbox, double &x, double &y, double &z);
Bbox *quadrant_bbox(Bbox *bbox, int &quadrant);
void compute_force(Node *root, double &x, double &y, double &z, double &m, Point3d *force);

#endif // BARNES_HUT_H
