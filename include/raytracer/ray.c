#include "ray.h"

/* Create a new ray. */
ray new_ray(tuple origin, tuple direction)
{
    ray r = {
        origin, direction
    };

    return r;
}

/* Find the position */
tuple position(ray* r, double t)
{
    /* r->origin + r->direction * t */
    tuple t0 = t_mul(t, &(r->direction));
    return t_add(&(r->origin), &t0);
}