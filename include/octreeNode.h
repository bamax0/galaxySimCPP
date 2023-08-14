#ifndef OCTREENODE_H
#define OCTREENODE_H

#include "bbox.h"
#include "star.h"
#include "point.h"
#include "util.h"

class OctreeNode
{
private:
    OctreeNode* child[8] = {nullptr};
    Bbox bbox;
    Point3d cm = Point3d();
    double m = 0;
    int nb_star = 0;

public:

    OctreeNode(const Bbox& bbox);
    ~OctreeNode();

    void appendStar(const Point3d& pos, const double& mass, const int& depth=0);
    Point3d compute_force(const Point3d &p, const double &m, const double& softening2) const;

private:
    int getSubBbox(const Point3d& pos, const double& mass);
    Bbox getSubBbox(int idx) const;
    int getSubBboxId(const Point3d& pos) const;

};

#endif