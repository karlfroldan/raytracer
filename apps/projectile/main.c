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

void tick(environment* env, projectile* proj, projectile* new_proj);

int main()
{
    tuple p_point, p_vector;
    tuple e_v1, e_v2;

    printf("Hello Projectile!\n");

    return 0;
}

void tick(environment* env, projectile* proj, projectile* new_proj)
{
    tuple new_pos, arg_1, new_vel;

    add_tuple(&(proj->position), &(proj->velocity), &new_pos);
    add_tuple(&(proj->velocity), &(env->gravity), &arg_1);
    add_tuple(&arg_1, &(env->wind), &new_vel);

    free(arg_1.arr);

    new_proj->position = new_pos;
    new_proj->velocity = new_vel;
}