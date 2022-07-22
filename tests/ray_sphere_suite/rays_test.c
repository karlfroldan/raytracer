#include "../bdd-for-c.h"

#include <raytracer/ray.h>
#include <raytracer/tuple.h>
#include <raytracer/sphere.h>

spec("Rays test")
{
    it("Creating and querying a ray")
    {
        tuple origin = point(1, 2, 3);
        tuple direction = vector(4, 5, 6);

        ray r = new_ray(origin, direction);

        check(t_approx(&origin, &r.origin));
        check(t_approx(&direction, &r.direction));
    }

    it("Computing a point from a distance")
    {
        ray r = new_ray(point(2, 3, 4), vector(1, 0, 0));

        tuple e1 = point(2, 3, 4);
        tuple e2 = point(3, 3, 4);
        tuple e3 = point(1, 3, 4);
        tuple e4 = point(4.5, 3, 4);

        tuple r1, r2, r3, r4;

        r1 = position(&r, 0);
        r2 = position(&r, 1);
        r3 = position(&r, -1);
        r4 = position(&r, 2.5);

        check(t_approx(&e1, &r1));
        check(t_approx(&e2, &r2));
        check(t_approx(&e3, &r3));
        check(t_approx(&e4, &r4));
    }
}