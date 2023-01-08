#include "initStar.h"

using namespace std;

double getRandomValue(){
    return (double)rand()/RAND_MAX;
}

double getRandomeValueBetween(double start, double end){
    return getRandomValue()*(end-start) + start;
}

void initStarDoubleGalaxy(star* tab_star, int nb_star, double dt) {
    double u, phi;
    int i;

    srand(time(NULL));
    for(i = 0; i<nb_star; i++){
        u = getRandomValue();
        phi = 2*PI*u;
        tab_star[i].x = pow(2*getRandomValue(), (double)1./3) * cos(phi);
        tab_star[i].y = pow(2*getRandomValue(), 1./3) * sin(phi);
        tab_star[i].mass = (double)1./nb_star;
        tab_star[i].vx = pow(2*getRandomValue(), (double)1./3) * ( -sin(phi) ) * 2*PI*1.4*dt;
        tab_star[i].vy = pow(2*getRandomValue(), (double)1./3) * cos(phi) * 2*PI*1.4*dt;
        tab_star[i].ax = 0;
        tab_star[i].ay = 0;

        if(i%2){
            tab_star[i].x += 3;
            tab_star[i].y += 3;
            tab_star[i].vx += 0.09;
            tab_star[i].vy += 0.09;
        } else {
            tab_star[i].x -= 3;
            tab_star[i].y -= 3;
            tab_star[i].vx -= 0.08;
            tab_star[i].vy -= 0.08;
        }
    }
    // Black hole !
    tab_star[0].x = 3;
    tab_star[0].y = 3;
    tab_star[0].mass = (double)1e4/nb_star;
    tab_star[0].vx = 0.4;
    tab_star[0].vy = 0.4;

    tab_star[1].x = -3;
    tab_star[1].y = -3;
    tab_star[1].mass = (double)1e5/nb_star;
    tab_star[0].vx = -0.2;
    tab_star[0].vy = -0.2;
}


void initStarCircle(star* tab_star, int nb_star, double dt) {
    double r, theta;
    double i, u;
    double pi = 3.14159265358;
    for(int j = 0; j<nb_star; j++){
        i = j +.2;
        r = 3*sqrt((double)i/nb_star);
        theta = pi*(1 + sqrt(5)) * i;
        
        tab_star[j].x = r*cos(theta);
        tab_star[j].y = r*sin(theta);
        tab_star[j].y = 0;

        tab_star[j].vx = -0.94/r*sin(theta);
        tab_star[j].vy = 0.94/r*cos(theta);
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
    float speed = 0.2;
    for(int j = 0; j<nb_star; j++){
        
        tab_star[j].x = getRandomeValueBetween(-size, size);
        tab_star[j].y = getRandomeValueBetween(-size, size);
        tab_star[j].z = getRandomeValueBetween(-0.2, 0.2);

        tab_star[j].mass = (double)getRandomeValueBetween(0.2, 7)/nb_star;
        
        tab_star[j].vx = getRandomeValueBetween(-speed, speed);
        tab_star[j].vy = getRandomeValueBetween(-speed, speed);
        tab_star[j].vz = getRandomeValueBetween(-speed, speed);
        
        tab_star[j].ax = 0;
        tab_star[j].ay = 0;
        tab_star[j].az = 0;
        if( getRandomeValueBetween(0, 1000) < 1 ) tab_star[j].mass = getRandomeValueBetween(15, 1000)/nb_star;
    }
}