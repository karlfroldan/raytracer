#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include "types.h"

/* Create a new ray. */
ray new_ray(tuple origin, tuple direction);

/* Find the position */
tuple position(ray* r, double t);

#endif 