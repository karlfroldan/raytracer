#ifndef RAYTRACER_MATRIX_H
#define RAYTRACER_MATRIX_H

#include "tuple.h"

/**
 * A 4x4 matrix specifically made for this raytracer project.
 * Each tuple in the matrix is one row.
 */
typedef struct matrix {
    tuple r1; 
    tuple r2;
    tuple r3;
    tuple r4;
} matrix;

/* Instantiate a new matrix.
The input is a list of values in row-major order.
If the list is shorter than 16 values, then the 
others will be filled with 0s. */
matrix m_new(double*, int);

/* 
 * Compares whether two matrices are approximated from each other. 
 * If their sizes are not equal, return 0.
 */
int m_approx(matrix*, matrix*);

#endif