#include "ray.h"
#include "tuple.h"
#include "matrix_transformations.h"
#include "matrix.h"

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

/* Create a new ray given some transformation. */
ray ray_transform(ray* r, matrix* m)
{
    tuple origin, direction;

    origin = m_mul_tuple(m, &(r->origin));
    direction = m_mul_tuple(m, &(r->direction));

    ray new_r = new_ray(origin, direction);

    return new_r;
}