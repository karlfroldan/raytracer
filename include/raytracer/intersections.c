#include "intersections.h"
#include "intersection_list.h"
#include "types.h"
#include "tuple.h"

#include <math.h>
#include <stdlib.h>


/* check whether a sphere and a ray intersects */
struct intersections 
sr_intersects(sphere* s, ray* r)
{
    struct intersections it;
    it.count = 0;
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
        double t_1, t_2;
        t_1 = (-b - sqrt(disc)) / (2 * a);
        t_2 = (-b + sqrt(disc)) / (2 * a);

        intersection_node n1 = intersection(t_1, (void*) s, OBJECT_SPHERE);
        intersection_node n2 = intersection(t_2, (void*) s, OBJECT_SPHERE);

        its_insert(&it, &n1);
        its_insert(&it, &n2);

        return it;
    }
}

/* Returns which intersection the ray hits. */
intersection_node* hit(struct intersections* its)
{
    if (its->count == 0)
        return NULL;
    
    intersection_node* temp;

    /* Usually, this is the minimum. */
    temp = tree_minimum(its->root);

    int should_be_null = 0;
    int counter = 0;

    /* Return the one with the lowest positive t_value. */
    while (temp != NULL && temp->t_value < 0)
    {
        temp = successor(temp);
        counter++;
    }

    if (counter == its->count)
        return NULL;

    return temp;
}