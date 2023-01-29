#ifndef NODE_H
#define NODE_H
#include "bbox.h"
#include "point.h"

class Node
{
public:
    Node *children[8];
    double mass;
    Point3d cm;
    Bbox *bbox;

    Node();

    ~Node();

    bool is_children_null();
    void set_quadrant(const int &new_quadrant);
};

#endif