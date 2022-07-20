#include "tuple.h"
#include <math.h> /* For fabs */
#include <stdlib.h>
#include <assert.h>

#include <stdio.h>

#include "raytracer_utils.h"

#define TRUE  1
#define FALSE 0



tuple t_new(double x, double y, double z, double w)
{
    tuple t = {
        x, y, z, w
    };

    return t;
}

/* Compare vectors. */ 
int t_approx(tuple* v1, tuple* v2)
{
    return approx_d(v1->x, v2->x) && approx_d(v1->y, v2->y) && 
        approx_d(v1->z, v2->z) && approx_d(v1->w, v2->w);
}

/* Add two vectors. */
tuple 
t_add(tuple* a, tuple* b) 
{
    tuple result = ZERO_T;

    result.x = a->x + b->x;
    result.y = a->y + b->y;
    result.z = a->z + b->z;
    result.w = a->w + b->w;

    return result;
}

tuple
t_sub(tuple* a, tuple* b) 
{
    tuple result = ZERO_T;

    result.x = a->x - b->x;
    result.y = a->y - b->y;
    result.z = a->z - b->z;
    result.w = a->w - b->w;

    return result;
}

/* Multiply a scalar and a vector. */
tuple
t_mul(double a, tuple* v) 
{
    tuple result = ZERO_T;

    result.x = v->x * a;
    result.y = v->y * a;
    result.z = v->z * a;
    result.w = v->w * a;

    return result;
}

/* Divide a tuple by a scalar. */
tuple 
t_div(double a, tuple* v)
{
    tuple result = ZERO_T;

    result.x = v->x / a;
    result.y = v->y / a;
    result.z = v->z / a;
    result.w = v->w / a;

    return result;
}

/* Negate a tuple. */
tuple 
t_negate(tuple* v) 
{
    tuple zero = ZERO_T;
    tuple result = t_sub(&zero, v);

    return result;
}

int
is_point(tuple* v) 
{
    return approx_d(v->w, 1);
}

int 
is_vector(tuple *v) 
{
    return approx_d(v->w, 0);
}

/* Hadamard Product of two tuples. */
tuple 
t_hadamard(tuple* v, tuple* w)
{
    tuple z = ZERO_T;

    z.x = v->x * w->x;
    z.y = v->y * w->y;
    z.z = v->z * w->z;
    z.w = v->w * w->w;

    return z;
}

tuple vector(double a, double b, double c)
{
    tuple v = {
        a, b, c, 0.0
    };

    return v;
}

tuple point(double a, double b, double c)
{
    tuple v = {
        a, b, c, 1.0
    };

    return v;
}



/* Compute the length of the vector, or magnitude. */
double
magnitude(tuple* v)
{
    double magnitude = 
        pow(v->x, 2) + pow(v->y, 2) + pow(v->z, 2) + pow(v->w, 2);

    return sqrt(magnitude);
}

/* Take an arbitrary vector and convert it into a unit vector */
tuple 
t_normalize(tuple* v)
{
    double m = magnitude(v);

    tuple result = {
        v->x / m,
        v->y / m,
        v->z / m,
        v->w / m
    };

    return result;
}

/* Get the dot product of two tuples */
double 
t_dot(tuple* v, tuple* w)
{
    double d = (v->x * w->x) + (v->y * w->y) +
        (v->z * w->z) + (v->w * w->w);

    return d;
}


/* Take an arbitrary vector and convert it into a unit vector */
tuple 
cross_product_4(tuple* a, tuple* b)
{
    return vector(
        a->y * b->z - a->z * b->y,
        a->z * b->x - a->x * b->z,
        a->x * b->y - a->y * b->x
    );
}

/* Print tuple. */
void t_print(tuple* v)
{
    printf("(%.3f, %.3f, %.3f, %.3f)", v->x, v->y, v->z, v->w);
}