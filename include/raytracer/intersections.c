#include "intersections.h"

#include "tuple.h"
#include <math.h>

/* check whether a sphere and a ray intersects */
intersection 
sr_intersects(sphere* s, ray* r)
{
    intersection it;
    tuple w_origin = point(0, 0, 0);
    tuple s_to_r = t_sub(&(r->origin), &w_origin);

    double a = t_dot(&(r->direction), &(r->direction));
    double b = 2 * t_dot(&(r->direction), &s_to_r);
    double c = t_dot(&s_to_r, &s_to_r) - 1;

    double disc = pow(b, 2) - (4 * a * c);

    /* If the discriminant is negative, then the ray misses the sphere. */
    if (disc < 0)
    {  
        it.count = 0;
        return it;
    }
    else
    {
        it.int_0 = (-b - sqrt(disc)) / (2 * a);
        it.int_1 = (-b + sqrt(disc)) / (2 * a);

        return it;
    }
}