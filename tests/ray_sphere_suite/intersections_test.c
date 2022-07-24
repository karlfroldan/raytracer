#include "../bdd_tap.h"

#include <raytracer/raytracer_utils.h>

#include <raytracer/intersection_list.h>
#include <raytracer/intersections.h>
#include <raytracer/sphere.h>

spec("Intersections test")
{
    it("An intersection encapsulates t and object")
    {
        sphere s = new_sphere();
        intersection_node i = intersection(3.5, (void*) &s, OBJECT_SPHERE);

        check(approx_d(i.t_value, 3.5));
        /* Also, the saved object is exactly the same. */
        sphere* s_ptr = (sphere*) i.obj_pntr;
        check(s_ptr == &s);
    }

    it("Aggregating intersections")
    {
        sphere s = new_sphere();

        intersection_node i1 = intersection(1, (void*) &s, OBJECT_SPHERE);
        intersection_node i2 = intersection(2, (void*) &s, OBJECT_SPHERE);

        struct intersections xs = new_intersections();

        its_insert(&xs, &i1);
        its_insert(&xs, &i2);

        intersection_node *rs1, *rs2, *rs3;

        rs1 = its_get(&xs, 0);
        rs2 = its_get(&xs, 1);
        rs3 = its_get(&xs, 3);

        check(rs3 == NULL);

        check(xs.count == 2);
        check(approx_d(rs1->t_value, 1));
        check(approx_d(rs2->t_value, 2));

        /* Check if they both point to the same object. */
        check((sphere*) rs1->obj_pntr == &s);  
        check((sphere*) rs2->obj_pntr == &s); 

        free_intersection_list(&xs); 
    }

    it("The hit, when all intersections have positive t.")
    {
        sphere s = new_sphere();

        intersection_node i1 = intersection(1, (void*) &s, OBJECT_SPHERE);
        intersection_node i2 = intersection(2, (void*) &s, OBJECT_SPHERE);

        struct intersections xs = new_intersections();

        its_insert(&xs, &i1);
        its_insert(&xs, &i2);

        intersection_node* i = hit(&xs);

        check(same_intersection(&i1, i));

        free_intersection_list(&xs); 
    }

    it("The hit, when some intersections have negative t.")
    {
        sphere s = new_sphere();

        intersection_node i1, i2, *i;

        i1 = intersection(-1, (void*) &s, OBJECT_SPHERE);
        i2 = intersection(1, (void*) &s, OBJECT_SPHERE);

        struct intersections xs = new_intersections();

        its_insert(&xs, &i1);
        its_insert(&xs, &i2);

        i = hit(&xs);

        check(same_intersection(&i2, i));

        free_intersection_list(&xs); 
    }

    it("The hit, when all intersections have negative t.")
    {
        sphere s = new_sphere();

        intersection_node i1, i2, *i;

        i1 = intersection(-2, (void*) &s, OBJECT_SPHERE);
        i2 = intersection(-1, (void*) &s, OBJECT_SPHERE);

        struct intersections xs = new_intersections();

        its_insert(&xs, &i1);
        its_insert(&xs, &i2);

        i = hit(&xs);

        check(i == NULL);

        free_intersection_list(&xs); 
    }

    it("The hit is always the lowest nonnegative intersection.")
    {
        sphere s = new_sphere();

        intersection_node i1, i2, i3, i4, *i;

        i1 = intersection(5, (void*) &s, OBJECT_SPHERE);
        i2 = intersection(7, (void*) &s, OBJECT_SPHERE);
        i3 = intersection(-3, (void*) &s, OBJECT_SPHERE);
        i4 = intersection(2, (void*) &s, OBJECT_SPHERE);

        struct intersections xs = new_intersections();

        its_insert(&xs, &i1);
        its_insert(&xs, &i2);
        its_insert(&xs, &i3);
        its_insert(&xs, &i4);

        i = hit(&xs);

        check(same_intersection(&i4, i));

        free_intersection_list(&xs); 
    }
}