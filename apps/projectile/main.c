#include <stdio.h>
#include <math.h>

#include <raytracer/tuple.h>
#include <raytracer/canvas.h>
#include <raytracer/color.h>

#define SCALE 35.25

typedef struct projectile
{
    tuple position;
    tuple velocity;
} projectile;

typedef struct environment
{
    tuple gravity;
    tuple wind;
} environment;

projectile tick(environment* env, projectile* proj);

int y_is_zero(projectile* p)
{
    return p->position.y < 0;
}

void write_to_canvas(canvas*, projectile*, double);

int main()
{
    tuple pos = point(0.0, 1.0, 0.0);
    tuple vel = vector(2.0, 2.0, 0.0);
    projectile p = {
        pos, t_normalize(&vel)
    };

    tuple gra = vector(0.0, -0.05, 0.0);
    tuple win = vector(-0.01, 0.0, 0.0);
    environment e = {
        gra, win
    };

    canvas proj_canvas = new_canvas(650, 400);

    printf("Initial position of projectile: ");
    t_print(&pos);
    printf("\nInitial velocity of projectile: ");
    t_print(&vel);
    printf("\nGravity: ");
    t_print(&gra);
    printf("\nWind: ");
    t_print(&win);
    printf("\n");

    int iter = 0;
    
    while (!y_is_zero(&p))
    {
        write_to_canvas(&proj_canvas, &p, SCALE);
        p = tick(&e, &p);

        iter++;
    }
    
    write_to_canvas(&proj_canvas, &p, SCALE);

    char* ppm_file = ppm(&proj_canvas);

    //printf("%s", ppm_file);
    FILE* outfile = fopen("projectile.ppm", "w");

    fprintf(outfile, "%s", ppm_file);

    fclose(outfile);

    return 0;
}

projectile tick(environment* env, projectile* proj)
{
    tuple temp = t_add(&(proj->velocity), &(env->gravity));

    projectile new_proj = {
        /* position + velocity */
        t_add(&(proj->position), &(proj->velocity)), /* Position */
        /* velocity + gravity + wind */
        t_add(&temp, &(env->wind)) /* velocity */
    };

    return new_proj;
}

void write_to_canvas(canvas* c, projectile* p, double scale)
{
    tuple p_pos = t_mul(scale, &(p->position));

    int x_pos = (int) round(p_pos.x);
    int y_pos = c->height - (int) round(p_pos.y);

    printf("x: %d, y: %d\n", x_pos, y_pos);

    if (x_pos >= 0 && y_pos >= 0 && x_pos < c->width && y_pos < c->height)
    {
        write_color(c, RED, x_pos, y_pos);

        // print neighbors.
        if (y_pos < 0)
            write_color(c, RED, x_pos, y_pos - 1);
        
        if (y_pos < c->height - 1)
            write_color(c, RED, x_pos, y_pos + 1);
        
        if (x_pos < 0)
            write_color(c, RED, x_pos - 1, y_pos);
        
        if (x_pos < c->width - 1)
            write_color(c, RED, x_pos + 1, y_pos);
    }
    else 
        fprintf(stderr, "NOT PRINTING... position out of bounds {x: %d, y: %d}\n", x_pos, y_pos);
}