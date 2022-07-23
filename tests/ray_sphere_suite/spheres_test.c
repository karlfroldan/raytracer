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

        struct intersections is = sr_intersects(&s, &r);

        intersection_node* n1 = its_get(&is, 0);
        intersection_node* n2 = its_get(&is, 1);

        check(is.count ==  2);
        check(approx_d(n1->t_value, 4.0));
        check(approx_d(n2->t_value, 6.0));

        /* Make sure they point to the actual sphere. */
        check(n1->obj_pntr == &s);
        check(n2->obj_pntr == &s);

        free_intersection_list(&is);
    }

    it("A ray intersects a sphere at a tangent")
    {
        ray r = new_ray(point(0, 1, -5), vector(0, 0, 1));
        sphere s = new_sphere();

        struct intersections is = sr_intersects(&s, &r);

        intersection_node* n1 = its_get(&is, 0);
        intersection_node* n2 = its_get(&is, 1);

        check(is.count ==  2);
        check(approx_d(n1->t_value, 5.0));
        check(approx_d(n2->t_value, 5.0));

        /* Make sure they point to the actual sphere. */
        check(n1->obj_pntr == &s);
        check(n2->obj_pntr == &s);

        free_intersection_list(&is);
    }

    it("A ray misses a sphere")
    {
        ray r = new_ray(point(0, 2, -5), vector(0, 0, 1));
        sphere s = new_sphere();

        struct intersections is = sr_intersects(&s, &r);

        check(is.count == 0);
    }

    it("A sphere is behind a ray")
    {
        ray r = new_ray(point(0, 0, 5), vector(0, 0, 1));
        sphere s = new_sphere();

        struct intersections is = sr_intersects(&s, &r);

        intersection_node* n1 = its_get(&is, 0);
        intersection_node* n2 = its_get(&is, 1);

        check(is.count ==  2);
        check(approx_d(n1->t_value, -6.0));
        check(approx_d(n2->t_value, -4.0));

        /* Make sure they point to the actual sphere. */
        check(n1->obj_pntr == &s);
        check(n2->obj_pntr == &s);

        free_intersection_list(&is);
    }
}