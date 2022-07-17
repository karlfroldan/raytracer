#include <stdio.h>
#include <raytracer/tuple.h>

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
    return _y(&(p->position)) < 0;
}

int main()
{
    tuple pos = point(0, 1, 0);
    tuple vel = vector(1, 1, 0);
    tuple gra = vector(0, -0.1, 0);
    tuple win = vector(-0.01, 0, 0);

    printf("Initial position of projectile: ");
    t_print(&pos);
    printf("\nInitial velocity of projectile: ");
    t_print(&vel);
    printf("\nGravity: ");
    t_print(&gra);
    printf("\nWind: ");
    t_print(&win);
    printf("\n");

    projectile p = {
        pos, t_normalize(&vel)
    };

    environment e = {
        gra, win
    };

    int iter = 0;
    
    while (!y_is_zero(&p))
    {
        printf("\nIter %d\n", iter);
        printf("Projectile position: ");
        t_print(&(p.position));
        printf("\n");

        p = tick(&e, &p);

        iter++;
    }

    t_free(&(p.position));
    t_free(&(p.velocity));
    t_free(&(e.gravity));
    t_free(&(e.wind));

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

    // garbage collect.
    t_free(&(proj->position));
    t_free(&(proj->velocity));

    return new_proj;
}