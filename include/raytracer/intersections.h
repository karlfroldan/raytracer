#ifndef RAYTRACER_INTERSECTIONS_H
#define RAYTRACER_INTERSECTIONS_H

#include "intersection_list.h"
#include "types.h"

/* check whether a sphere and a ray intersects */
struct intersections
sr_intersects(sphere*, ray*);

/* Returns which intersection the ray hits. */
intersection_node* hit(struct intersections* its);

#endif