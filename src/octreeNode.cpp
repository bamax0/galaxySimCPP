#include "octreeNode.h"

OctreeNode::OctreeNode(const Bbox &bbox) : bbox(bbox)
{}

OctreeNode::~OctreeNode()
{
    for (int i = 0; i < 8; ++i)
        {
            if (this->child[i] != nullptr)
            {
                delete this->child[i];
            }
        }
}

void OctreeNode::appendStar(const Point3d& star_pos, const double& star_mass, const int& depth)
{
    if(this->nb_star == 1){
        int idx = this->getSubBbox(this->cm, this->m);
        this->child[idx]->appendStar(this->cm, this->m, depth+1);
    }

    if(this->nb_star >= 1){
        int idx = this->getSubBbox(star_pos, star_mass);
        this->child[idx]->appendStar(star_pos, star_mass, depth+1);
    }
    double mass = this->m + star_mass + 1e-4;
    this->cm = (this->cm*this->m + star_pos*star_mass)/mass;
    this->m = mass;
    this->nb_star += 1;
}

int OctreeNode::getSubBbox(const Point3d& pos, const double& mass)
{
    int idx = this->getSubBboxId(pos);
    if(this->child[idx] == nullptr){
        this->child[idx] = new OctreeNode(this->getSubBbox(idx));
    }

    return idx;
}

Bbox OctreeNode::getSubBbox(int idx) const
{
    double subBbboxSize = this->bbox.size/2;
    Bbox subBbbox(this->bbox.p, subBbboxSize);

    if(idx%2){
        subBbbox.p.x += subBbboxSize;
    }

    if(idx == 2 || idx == 3 || idx == 6 || idx == 7){
        subBbbox.p.y += subBbboxSize;
    }

    if(idx >= 4){
        subBbbox.p.z += subBbboxSize;
    }

    return subBbbox;
}


int OctreeNode::getSubBboxId(const Point3d& pos) const
{
    int idx = 0;
    double subBbboxSize = this->bbox.size/2;
    if(this->bbox.p.x + subBbboxSize < pos.x){
        idx += 1;
    }
    
    if(this->bbox.p.y + subBbboxSize < pos.y){
        idx += 2;
    }

    if(this->bbox.p.z + subBbboxSize < pos.z){
        idx += 4;
    }

    return idx;
}

double theta = 0.5;

Point3d OctreeNode::compute_force(const Point3d &p, const double &m, const double& softening2) const
{
    if (this->m == 0)
        return Point3d();

    if(this->nb_star == 1 && this->cm == p && this->m == m)
        return Point3d();

    double dx = this->cm.x - p.x;
    double dy = this->cm.y - p.y;
    double dz = this->cm.z - p.z;

    double r2 = dx*dx + dy*dy + dz*dz + softening2;
    double inv_r = invsqrtQuake(r2 * r2 * r2);

    if (this->bbox.size * inv_r * r2 < theta || this->nb_star == 1)
    {
        double norm_f = m * this->m * inv_r;
        return Point3d(norm_f * dx, norm_f * dy, norm_f * dz);
    }
    else
    {
        Point3d force = Point3d();
        for (int i = 0; i < 8; ++i)
        {
            if (this->child[i] != nullptr)
            {
                force += this->child[i]->compute_force(p, m, softening2);
            }
        }
        return force;
    }
}