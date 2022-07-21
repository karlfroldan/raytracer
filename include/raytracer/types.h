#ifndef RAYTRACER_TYPES_H
#define RAYTRACER_TYPES_H

/* A struct representing a color. */
typedef struct color
{
    double red;
    double green;
    double blue;
} color;

/* 
 * A vector is a fixed-size array of numbers closed under the following operations:
 * 1. Vector-to-vector addition
 * 2. Vector-to-scalar/scalar-to-vector multiplication.
 */
typedef struct tuple
{
    double x;
    double y;
    double z;
    double w;
} tuple;

/**
 * A 4x4 matrix specifically made for this raytracer project.
 * Each tuple in the matrix is one row.
 */
typedef struct matrix {
    tuple r1; 
    tuple r2;
    tuple r3;
    tuple r4;

    int dims;
} matrix;

typedef struct sphere 
{
    int uid;
} sphere;

typedef struct ray 
{
    tuple origin;
    tuple direction;
} ray;


#endif