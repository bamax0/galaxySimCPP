#include "node.h"

bool Node::is_children_null()
{
    for (int k = 0; k < 8; ++k)
    {
        if (children[k] != nullptr)
            return false;
    }
    return true;
}

Node::Node() : cm(), mass()
{
    for (int k = 0; k < 8; ++k)
        children[k] = nullptr;
}

Node::~Node()
{
    for (int k = 0; k < 8; ++k)
        delete children[k];

    delete bbox;
}

void Node::set_quadrant(const int &quadrant)
{
    if (children[quadrant] == nullptr)
    {
        children[quadrant] = new Node();
        children[quadrant]->bbox = bbox->get_quadrant(quadrant);
    }
}