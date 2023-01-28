#include "barnes_hut.h"
using namespace std;

double softening = 0.1;
double theta = 0.5;
double softening2 = softening * softening;

void quad_insert(Node *root, Point3d &p, double &m)
{
    double root_mass = root->mass;
    if (root_mass == 0)
    {
        root->mass = m;
        root->cm = p;
    }
    else if (root->is_children_null())
    {
        int old_quadrant = quadrant_of_particle(root->bbox, root->cm);
        root->children[old_quadrant] = new Node();
        root->children[old_quadrant]->bbox = quadrant_bbox(root->bbox, old_quadrant);
        quad_insert(root->children[old_quadrant], root->cm, root_mass);
        int new_quadrant = quadrant_of_particle(root->bbox, p);
        if (root->children[new_quadrant] == NULL)
        {
            root->children[new_quadrant] = new Node();
            root->children[new_quadrant]->bbox = quadrant_bbox(root->bbox, new_quadrant);
        }
        quad_insert(root->children[new_quadrant], p, m);
        root->cm = (root->cm * root_mass + p * m) / (root_mass + m);
        root->mass = root_mass + m;
    }
    else
    {
        int new_quadrant = quadrant_of_particle(root->bbox, p);
        if (root->children[new_quadrant] == nullptr)
        {
            root->children[new_quadrant] = new Node();
            root->children[new_quadrant]->bbox = quadrant_bbox(root->bbox, new_quadrant);
        }
        quad_insert(root->children[new_quadrant], p, m);
        root->cm = (root->cm * root_mass + p * m) / (root_mass + m);
        root->mass = root_mass + m;
    }
}

void compute_force(Node *root, Point3d &p, double &m, Point3d *force)
{
    force->x = 0;
    force->y = 0;
    force->z = 0;
    if (root->mass == 0)
        return;
    if (root->cm == p)
        return;

    double d = root->bbox->x2 - root->bbox->x1;

    double dx = root->cm.x - p.x;
    double dy = root->cm.y - p.y;
    double dz = root->cm.z - p.z;
    double r2 = dx * dx + dy * dy + dz * dz + softening2;
    double inv_r = invsqrtQuake(r2 * r2 * r2);
    if (d * inv_r * r2 < theta || root->is_children_null())
    {
        double norm_f = m * root->mass * inv_r;
        force->x = norm_f * dx;
        force->y = norm_f * dy;
        force->z = norm_f * dz;
    }
    else
    {
        Point3d *force2 = new Point3d();
        Node **children = root->children;
        for (int i = 0; i < 8; ++i)
        {
            if (children[i] != nullptr)
            {
                compute_force(children[i], p, m, force2);
                *force += *force2;
            }
        }
        delete force2;
    }
}

Bbox *find_root_bbox(Star3d *galaxy, int &nb_star)
{
    double xmin = galaxy[0].pos.x;
    double xmax = xmin;
    double ymin = galaxy[0].pos.y;
    double ymax = ymin;
    double zmin = galaxy[0].pos.z;
    double zmax = zmin;

    double x, y, z;
    for (int i = 0; i < nb_star; ++i)
    {
        x = galaxy[i].pos.x;
        y = galaxy[i].pos.y;
        z = galaxy[i].pos.z;
        if (x > xmax)
            xmax = x;
        if (x < xmin)
            xmin = x;

        if (y > ymax)
            ymax = y;
        if (y < ymin)
            ymin = y;

        if (z > zmax)
            zmax = z;
        if (z < zmin)
            zmin = z;
    }
    Bbox *b = new Bbox();
    b->x1 = xmin;
    b->y1 = ymin;
    b->z1 = zmin;
    double delta_x = xmax - xmin;
    double delta_y = ymax - ymin;
    double delta_z = zmax - zmin;

    b->x2 = xmax;
    b->y2 = ymax;
    b->z2 = zmax;
    //////////////////////////////////////////////////////////////////////////////////////////
    if (delta_x > delta_y && delta_x > delta_z)
    {
        b->y2 += delta_x - delta_y;
        b->z2 += delta_x - delta_z;
    }
    else if (delta_y > delta_x && delta_y > delta_z)
    {
        b->x2 += delta_y - delta_x;
        b->z2 += delta_y - delta_z;
    }
    else
    {
        b->x2 += delta_z - delta_z;
        b->y2 += delta_z - delta_y;
    }

    return b;
}

//
int quadrant_of_particle(Bbox *bbox, Point3d &p)
{

    if (2 * p.z <= bbox->z2 + bbox->z1)
    {
        if (2 * p.y >= bbox->y2 + bbox->y1)
        {
            if (2 * p.x <= bbox->x2 + bbox->x1)
                return 0;
            else
                return 1;
        }
        else
        {
            if (2 * p.x >= bbox->x2 + bbox->x1)
                return 2;
            else
                return 3;
        }
    }
    else
    {
        if (2 * p.y >= bbox->y2 + bbox->y1)
        {
            if (2 * p.x <= bbox->x2 + bbox->x1)
                return 4;
            else
                return 5;
        }
        else
        {
            if (2 * p.x >= bbox->x2 + bbox->x1)
                return 6;
            else
                return 7;
        }
    }
}

Bbox *quadrant_bbox(Bbox *bbox, int &quadrant)
{
    Bbox *b = new Bbox();
    double x = (bbox->x1 + bbox->x2) / 2.;
    double y = (bbox->y1 + bbox->y2) / 2.;
    double z = (bbox->z1 + bbox->z2) / 2.;
    // Quadrant 0: (xmin, x, y, ymax)
    switch (quadrant)
    {
    case 0:
        b->x1 = bbox->x1;
        b->y1 = y;
        b->z1 = z;

        b->x2 = x;
        b->y2 = bbox->y2;
        b->z2 = bbox->z2;
        break;
    case 1:
        b->x1 = x;
        b->y2 = bbox->y2;
        b->z2 = bbox->z2;

        b->x2 = bbox->x2;
        b->y1 = y;
        b->z1 = z;
        break;
    case 2:
        b->x2 = bbox->x2;
        b->y2 = y;
        b->z2 = bbox->z2;

        b->x1 = x;
        b->y1 = bbox->y1;
        b->z1 = z;
        break;
    case 3:
        b->x1 = bbox->x1;
        b->y1 = bbox->y1;
        b->z1 = z;

        b->x2 = x;
        b->z2 = bbox->z2;
        b->y2 = y;

        break;

    case 4:
        b->x1 = bbox->x1;
        b->y1 = y;
        b->z1 = bbox->z1;

        b->x2 = x;
        b->y2 = bbox->y2;
        b->z2 = z;
        break;
    case 5:
        b->x2 = bbox->x2;
        b->y2 = bbox->y2;
        b->z2 = z;

        b->x1 = x;
        b->y1 = y;
        b->z1 = bbox->z1;
        break;
    case 6:
        b->x1 = x;
        b->y1 = bbox->y1;
        b->z1 = bbox->z1;

        b->x2 = bbox->x2;
        b->y2 = y;
        b->z2 = z;
        break;
    case 7:
        b->x1 = bbox->x1;
        b->y1 = bbox->y1;
        b->z1 = bbox->z1;

        b->x2 = x;
        b->y2 = y;
        b->z2 = z;
        break;
    }
    return b;
}
