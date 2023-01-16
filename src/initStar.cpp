#include "initStar.h"
#include <cmath>
#include <random>

using namespace std;

double getRandomValue(){
    return (double)rand()/RAND_MAX;
}

double getRandomValueBetween(double start, double end){
    return getRandomValue()*(end-start) + start;
}

void initSphereGalaxy(star* tab_star, int nb_star, double dt) {
    double r, phi, theta;
    double v_theta, v_phi, v_r;
    int i;
    double galaxyRadius = 4.0;
    double galaxy_velocity = 0.5;

    srand(time(NULL));

    for(i = 0; i<nb_star; i++){
        theta = 2 * M_PI * getRandomValue();
        phi = acos(2 * getRandomValue() - 1);
        r = getRandomValueBetween(0.1, galaxyRadius);
        // calculate the position of the star
        tab_star[i].x = galaxyRadius * sin(phi) * cos(theta);
        tab_star[i].y = galaxyRadius * sin(phi) * sin(theta);
        tab_star[i].z = galaxyRadius * cos(phi);
        tab_star[i].mass = (double)getRandomValueBetween(10, 400)/nb_star;

        v_theta = 2 * M_PI * getRandomValue();
        v_phi = acos(2 * getRandomValue() - 1);
        v_r = getRandomValueBetween(0, galaxy_velocity);

        tab_star[i].vx = v_r * sin(v_phi) * cos(v_theta);
        tab_star[i].vy = v_r * sin(v_phi) * sin(v_theta);
        tab_star[i].vz = v_r * cos(v_phi);

        tab_star[i].ax = 0;
        tab_star[i].ay = 0;
        tab_star[i].az = 0;
    }
}


void initStarCircle(star* tab_star, int nb_star, double dt) {
    double r, theta;
    double i, u;
    double pi = 3.14159265358;
    for(int j = 0; j<nb_star; j++){
        i = j +.05;
        r = 3*sqrt((double)i/nb_star);
        theta = pi*(1 + sqrt(5)) * i;
        
        tab_star[j].x = r*cos(theta);
        tab_star[j].y = r*sin(theta);
        tab_star[j].y = 0;

        tab_star[j].vx = -0.5/r*sin(theta);
        tab_star[j].vy = 0.5/r*cos(theta);
        tab_star[j].vz = 0;

        u = 4*getRandomValue() + 0.2;
        tab_star[j].mass = (double)u/nb_star;
        tab_star[j].ax = 0;
        tab_star[j].ay = 0;
        tab_star[j].az = 0;
    }
    
    tab_star[0].mass = (double)10000./nb_star;

    tab_star[nb_star/5].mass = (double)300./nb_star;
    tab_star[nb_star/2].mass = (double)300./nb_star;
    tab_star[nb_star-10].mass = (double)300./nb_star;
}

void initStarUniverse(star* tab_star, int nb_star, double dt) {
    float size = 2;
    float speed = 0.1;
    for(int j = 0; j<nb_star; j++){
        
        tab_star[j].x = getRandomValueBetween(-size, size);
        tab_star[j].y = getRandomValueBetween(-size, size);
        tab_star[j].z = getRandomValueBetween(-0.2, 0.2);

        tab_star[j].mass = (double)getRandomValueBetween(0.2, 7)/nb_star;
        
        tab_star[j].vx = getRandomValueBetween(-speed, speed);
        tab_star[j].vy = getRandomValueBetween(-speed, speed);
        tab_star[j].vz = getRandomValueBetween(-speed, speed);
        
        tab_star[j].ax = 0;
        tab_star[j].ay = 0;
        tab_star[j].az = 0;
        if( getRandomValueBetween(0, 1000) < 1 ) tab_star[j].mass = getRandomValueBetween(15, 1000)/nb_star;
    }
}


void initStarPlummer(star* galaxy, int nb_star, double scale_length)
{

    int N = nb_star; // number of stars
    double M = 1.0; // total mass of the galaxy
    double R = 3.0; // scale radius of the galaxy
    double V = 1.0; // scale velocity of the galaxy
    double flattening = 0.2; // flattening of the galaxy

    // Initialize the positions and velocities of the stars
    for (int i = 0; i < N; i++) {
        double r = R * pow(pow(getRandomValue(), -2.0/3.0) - 1.0, -1.0/2.0);
        double phi = 2 * M_PI * getRandomValue();
        double theta = acos(2 * getRandomValue() - 1);
        double z = r * flattening * cos(theta);
        double x = r * sqrt(1 - flattening * flattening) * cos(phi);
        double y = r * sqrt(1 - flattening * flattening) * sin(phi);
        double v = V * pow(r, 0.5);
        double v_phi = v * sqrt(1 - flattening * flattening) / r;
        double v_z = v * flattening * cos(theta) / r;
        galaxy[i].x = x;
        galaxy[i].y = y;
        galaxy[i].z = z;

        galaxy[i].vx = -v_phi * sin(phi);
        galaxy[i].vy = v_phi * cos(phi);
        galaxy[i].vz = v_z;

        galaxy[i].mass = M / N;

        galaxy[i].ax = 0.0;
        galaxy[i].ay = 0.0;
        galaxy[i].az = 0.0;
    }
}