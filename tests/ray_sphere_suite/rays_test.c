#include "../bdd_tap.h"

#include <raytracer/ray.h>
#include <raytracer/tuple.h>
#include <raytracer/sphere.h>
#include <raytracer/matrix.h>
#include <raytracer/matrix_transformations.h>

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

    it("Translating a ray")
    {
        ray r = new_ray(point(1, 2, 3), vector(0, 1, 0));
        matrix m = translate(3, 4, 5);

        ray r2 = ray_transform(&r, &m);

        tuple origin_e = point(4, 6, 8);
        tuple direct_e = vector(0, 1, 0);

        check(t_approx(&(r2.origin), &origin_e));
        check(t_approx(&(r2.direction), &direct_e));
    }

    it("Scaling a ray")
    {
        ray r = new_ray(point(1, 2, 3), vector(0, 1, 0));
        matrix m = scale(2, 3, 4);

        ray r2 = ray_transform(&r, &m);

        tuple origin_e = point(2, 6, 12);
        tuple direct_e = vector(0, 3, 0);

        check(t_approx(&(r2.origin), &origin_e));
        check(t_approx(&(r2.direction), &direct_e));
    }
}