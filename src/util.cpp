#include "util.h"

void saveMass(Star3d *stars, int nb_star)
{
    FILE *f = fopen("./data/mass", "w+");
    fprintf(f, "m\n");
    for (int i = 0; i < nb_star; i++)
        fprintf(f, "%i\n", stars[i].mass);
    fclose(f);
    return;
}

int cpt_save = 0;
void saveStar(Star3d *stars, int nb_star)
{
    int size = 3;
    int height = 1800;
    int width = 1800;
    int depth = 1800;
    int x, y, z;
    char name[90];
    sprintf(name, "./data/sav_%i", cpt_save);
    FILE *f = fopen(name, "w+");
    Star3d s;
    fprintf(f, "x;y;z\n");
    for (int i = 0; i < nb_star; i++)
    {
        s = stars[i];
        x = (s.pos.x / size * width / 2) + width / 2;
        y = (s.pos.y / size * height / 2) + height / 2;
        z = (s.pos.z / size * depth / 2) + depth / 2;
        fprintf(f, "%i;%i;%i\n", x, y, z);
    }

    ++cpt_save;
    fclose(f);
    return;
}

double invsqrtQuake(double number)
{
    double y = number;
    double x2 = y * 0.5;
    int64_t i = *(int64_t *)&y;
    // The magic number is for doubles is from https://cs.uwaterloo.ca/~m32rober/rsqrt.pdf
    i = 0x5fe6eb50c7b537a9 - (i >> 1);
    y = *(double *)&i;
    y = y * (1.5 - (x2 * y * y)); // 1st iteration
    //      y  = y * ( 1.5 - ( x2 * y * y ) );   // 2nd iteration, this can be removed
    return y;
}

double getRandomValue()
{
    return (double)rand() / RAND_MAX;
}

double getRandomValueBetween(const double start, const double end)
{
    return getRandomValue() * (end - start) + start;
}