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

    int dims;
} matrix;

/* Instantiate a new matrix.
The input is a list of values in row-major order.
If the list is shorter than 16 values, then the 
others will be filled with 0s. */
matrix m_new(double*, int, int);

/* Create a 2x2 matrix. */
matrix m_2(double*, int);

/* Create a 3x3 matrix. */
matrix m_3(double*, int);

/* Create a 4x4 matrix. */
matrix m_4(double*, int);

/* Create a zero matrix of some dimension. */
matrix m_zero(int);

/* Identity matrix */
matrix m_id(int);


/* 
 * Compares whether two matrices are approximated from each other. 
 * If their sizes are not equal, return 0.
 */
int m_approx(matrix*, matrix*);

/* Get the value of the matrix at some coordinate */
double m_at(matrix*, int x, int y);

/* Change the value of the matrix at */
void m_update_at(matrix*, int x, int y, double v);

/* Print the matrix. */
void m_print(matrix*);

/* Matrix transpose  */
matrix transpose(matrix*);

/* Matrix algebra. */

/* Multiply two matrices. */
matrix m_mul(matrix*, matrix*);

/* Matrix multiplied by a tuple. */
tuple m_mul_tuple(matrix*, tuple*);

#endif