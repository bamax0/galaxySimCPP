#ifndef BARNES_HUT_H
#define BARNES_HUT_H
#include "star.h"
#include "util.h"
#include "node.h"
#include "bbox.h"
#include "point.h"

Bbox *find_root_bbox(Star3d *galaxy, int &nb_star);
void quad_insert(Node *root, Point3d &p, double &m);
int quadrant_of_particle(Bbox *bbox, Point3d &p);
Bbox *quadrant_bbox(Bbox *bbox, int &quadrant);
void compute_force(Node *root, Point3d &p, double &m, Point3d *force);

#endif // BARNES_HUT_H
