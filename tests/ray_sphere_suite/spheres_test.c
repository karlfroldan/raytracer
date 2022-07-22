#include "../bdd-for-c.h"

#include <raytracer/intersections.h>
#include <raytracer/sphere.h>
#include <raytracer/ray.h>
#include <raytracer/tuple.h>
#include <raytracer/raytracer_utils.h>

spec("Spheres tests")
{
    it("A ray intersects a sphere at two points.")
    {
        ray r = new_ray(point(0, 0, -5), vector(0, 0, 1));
        sphere s = new_sphere();

        intersection is = sr_intersects(&s, &r);

        check(is.count ==  2);
        check(approx_d(is.int_0, 4.0))
        check(approx_d(is.int_1, 6.0));
    }

    it(" A ray intersects a sphere at a tangent")
    {
        ray r = new_ray(point(0, 1, -5), vector(0, 0, 1));
        sphere s = new_sphere();

        intersection is = sr_intersects(&s, &r);

        check(is.count ==  2);
        check(approx_d(is.int_0, 5.0))
        check(approx_d(is.int_1, 5.0));
    }

    it("A ray misses a sphere")
    {
        ray r = new_ray(point(0, 2, -5), vector(0, 0, 1));
        sphere s = new_sphere();

        intersection is = sr_intersects(&s, &r);

        check(is.count == 0);
    }

    it("A sphere is behind a ray")
    {
        ray r = new_ray(point(0, 0, 5), vector(0, 0, 1));
        sphere s = new_sphere();

        intersection is = sr_intersects(&s, &r);

        check(is.count ==  2);
        check(approx_d(is.int_0, -6.0))
        check(approx_d(is.int_1, -4.0));
    }
}