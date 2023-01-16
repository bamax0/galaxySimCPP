#include "barnes_hut.h"
using namespace std;

double softening = 0.1;
double theta = 0.5;
double softening2 = softening*softening;


void quad_insert(Node* root, double& x, double& y, double& z, double& m){
    double root_mass = root->mass;
    if( root_mass == 0 ) {
        root->mass = m;
        root->cm_x = x;
        root->cm_y = y;
        root->cm_z = z;
    } else if(root->is_children_null()) {
        int old_quadrant = quadrant_of_particle(root->bbox, root->cm_x, root->cm_y, root->cm_z);
        root->children[old_quadrant] = new Node();
        root->children[old_quadrant]->bbox = quadrant_bbox(root->bbox, old_quadrant);
        quad_insert(root->children[old_quadrant], root->cm_x, root->cm_y, root->cm_z, root_mass);
        int new_quadrant = quadrant_of_particle(root->bbox, x, y, z);
        if( root->children[new_quadrant] == NULL ) {
            root->children[new_quadrant] = new Node();
            root->children[new_quadrant]->bbox = quadrant_bbox(root->bbox, new_quadrant);
        }
        quad_insert(root->children[new_quadrant], x, y, z, m);
        root->cm_x = (root->cm_x*root_mass + x*m) / (root_mass + m);
        root->cm_y = (root->cm_y*root_mass + y*m) / (root_mass + m);
        root->cm_z = (root->cm_z*root_mass + z*m) / (root_mass + m);
        root->mass = root_mass + m;
    } else {
        int new_quadrant = quadrant_of_particle(root->bbox, x, y, z);
        if( root->children[new_quadrant] == nullptr ) {
            root->children[new_quadrant] = new Node();
            root->children[new_quadrant]->bbox = quadrant_bbox(root->bbox, new_quadrant);
        }
        quad_insert(root->children[new_quadrant], x, y, z, m);
        root->cm_x = (root->cm_x*root_mass + x*m) / (root_mass + m);
        root->cm_y = (root->cm_y*root_mass + y*m) / (root_mass + m);
        root->cm_z = (root->cm_z*root_mass + z*m) / (root_mass + m);
        root->mass = root_mass + m;
    }

}

void integrate(star* galaxy, int& nb_star, double& dt, double& T) {
    double dt_2 = dt/2;
    int cptCapt = 10;
    int cpt = 0;

    double *force  = new double[3];
    double *partricles_force_x = new double[nb_star];
    double *partricles_force_y = new double[nb_star];
    double *partricles_force_z = new double[nb_star];

    time_t begin = time(NULL);
    star s;
    int minute;
    saveMass(galaxy, nb_star);

    cout << "start" << endl;
    for(double t=0; t<T; t+=dt) {
        Node* root = new Node;
        root->bbox = find_root_bbox(galaxy, nb_star);
        for( int i=0; i<nb_star; ++i){
            s = galaxy[i];
            quad_insert(root, s.x, s.y, s.z, s.mass);
        }
        for( int i=0; i<nb_star; ++i){
            s = galaxy[i];
            compute_force(root, s.x, s.y, s.z, s.mass, force);
            partricles_force_x[i] = force[0];
            partricles_force_y[i] = force[1];
            partricles_force_z[i] = force[2];
        }
        for( int i=0; i<nb_star; ++i) {
            star* s = &galaxy[i];

            s->vx += s->ax*dt_2;
            s->vy += s->ay*dt_2;
            s->vz += s->az*dt_2;

            s->ax = partricles_force_x[i] / s->mass;
            s->ay = partricles_force_y[i] / s->mass;
            s->az = partricles_force_z[i] / s->mass;

            s->vx += s->ax*dt_2;
            s->vy += s->ay*dt_2;
            s->vz += s->az*dt_2;

            s->x += s->vx*dt;
            s->y += s->vy*dt;
            s->z += s->vz*dt;

        }
        if(cpt%cptCapt == 0) {
            time_t end = time(NULL);
            if(t){
                minute = (int)(end-begin)*(T/t-1);
                cout <<  (int)(t/T*10000)/100. << "\% time left: " 
                << (int)(minute/60/60) << "h " << (minute/60)%60 
                << "m (time :" << (int)(end-begin)/60 << "m )" << endl;

            }
            saveStar(galaxy, nb_star);
        }
        ++cpt;
        delete root;

    }
    delete[] force;
    delete[] partricles_force_x;
    delete[] partricles_force_y;
    delete[] partricles_force_z;
}


void compute_force(Node* root, double& x, double& y, double& z, double& m, double* force) {
    force[0] = 0;
    force[1] = 0;
    force[2] = 0;
    if( root->mass == 0 ) return;
    if( root->cm_x == x && root->cm_y == y && root->cm_z == z) return;

    double d = root->bbox->x2 - root->bbox->x1;

    double dx = root->cm_x - x;
    double dy = root->cm_y - y;
    double dz = root->cm_z - z;
    double r2 = dx*dx + dy*dy + dz*dz + softening2;
    double inv_r = invsqrtQuake(r2*r2*r2);
    if(d*inv_r*r2 < theta || root->is_children_null()) {
        double norm_f = m*root->mass*inv_r;
        force[0] = norm_f*dx;
        force[1] = norm_f*dy;
        force[2] = norm_f*dz;
    } else {
        double *force2 = new double[3];
        Node **children = root->children;
        for(int i=0; i<4; ++i) {
            if( children[i] != nullptr ) {
                compute_force(children[i], x, y, z, m, force2);
                force[0] += force2[0];
                force[1] += force2[1];
                force[2] += force2[2];
            }
        }
        delete[] force2;
    }
}

Bbox* find_root_bbox(star* galaxy, int& nb_star) {
    double xmin = galaxy[0].x;
    double xmax = xmin;
    double ymin = galaxy[0].y;
    double ymax = ymin;
    double zmin = galaxy[0].z;
    double zmax = zmin;


    double x, y, z;
    for(int i=0; i<nb_star; ++i) {
        x = galaxy[i].x;
        y = galaxy[i].y;
        z = galaxy[i].z;
        if( x > xmax ) xmax = x;
        if( x < xmin ) xmin = x;

        if( y > ymax ) ymax = y;
        if( y < ymin ) ymin = y;

        if( z > zmax ) zmax = z;
        if( z < zmin ) zmin = z;
    }
    Bbox* b = new Bbox();
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
    if( delta_x > delta_y && delta_x > delta_z) {
        b->y2 += delta_x-delta_y;
        b->z2 += delta_x-delta_z;
    } else if(delta_y > delta_x && delta_y > delta_z) {
        b->x2 += delta_y-delta_x;
        b->z2 += delta_y-delta_z;
    } else {
        b->x2 += delta_z-delta_z;
        b->y2 += delta_z-delta_y;
    }

    return b;
}

//
int quadrant_of_particle(Bbox* bbox, double& x, double& y, double& z) {

    if( 2*z <= bbox->z2 + bbox->z1 ) {
        if( 2*y >= bbox->y2 + bbox->y1 ) {
            if( 2*x <= bbox->x2 + bbox->x1 ) return 0;
            else return 1;
        } else {
            if( 2*x >= bbox->x2 + bbox->x1 ) return 2;
            else return 3;
        }
    } else {
        if( 2*y >= bbox->y2 + bbox->y1 ) {
            if( 2*x <= bbox->x2 + bbox->x1 ) return 4;
            else return 5;
        } else {
            if( 2*x >= bbox->x2 + bbox->x1 ) return 6;
            else return 7;
        }
    }
}

Bbox* quadrant_bbox(Bbox* bbox, int& quadrant) {
    Bbox* b = new Bbox();
    double x = (bbox->x1 + bbox->x2)/2.;
    double y = (bbox->y1 + bbox->y2)/2.;
    double z = (bbox->z1 + bbox->z2)/2.;
    // Quadrant 0: (xmin, x, y, ymax)
    switch(quadrant) {
        case 0:
            b->x1 = bbox->x1;
            b->x2 = x;

            b->y1 = y;
            b->y2 = bbox->y2;

            b->z1 = z;
            b->z2 = bbox->z2;
            break;
        case 1:
            b->x1 = x;
            b->x2 = bbox->x2;

            b->y1 = y;
            b->y2 = bbox->y2;

            b->z1 = z;
            b->z2 = bbox->z2;
            break;
        case 2:
            b->x1 = x;
            b->x2 = bbox->x2;

            b->y1 = bbox->y1;
            b->y2 = y;

            b->z1 = z;
            b->z2 = bbox->z2;
            break;
        case 3:
            b->x1 = bbox->x1;
            b->x2 = x;

            b->y1 = bbox->y1;
            b->y2 = y;

            b->z1 = z;
            b->z2 = bbox->z2;
            break;

        case 4:
            b->x1 = bbox->x1;
            b->x2 = x;

            b->y1 = y;
            b->y2 = bbox->y2;

            b->z1 = bbox->z1;
            b->z2 = z;
            break;
        case 5:
            b->x1 = x;
            b->x2 = bbox->x2;

            b->y1 = y;
            b->y2 = bbox->y2;

            b->z1 = bbox->z1;
            b->z2 = z;
            break;
        case 6:
            b->x1 = x;
            b->x2 = bbox->x2;

            b->y1 = bbox->y1;
            b->y2 = y;

            b->z1 = bbox->z1;
            b->z2 = z;
            break;
        case 7:
            b->x1 = bbox->x1;
            b->x2 = x;
            
            b->y1 = bbox->y1;
            b->y2 = y;

            b->z1 = bbox->z1;
            b->z2 = z;
            break;
    }
    return b;
}
