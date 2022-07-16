#ifndef RMATH_VECTOR_H
#define RMATH_VECTOR_H

/* An epsilon for approximated equality between two numbers. */
const double EPSILON = 0.00001;

/* Compare whether two doubles are approx. */
int approx_d(double, double);

/* 
 * A vector is a fixed-size array of numbers closed under the following operations:
 * 1. Vector-to-vector addition
 * 2. Vector-to-scalar/scalar-to-vector multiplication.
 */
struct vec
{
    double *arr; /* Our implementation of a vector can only contain doubles. */
    int    size; /* How many elements are there in our vector. */
};

/*********************
 * VECTOR OPERATIONS *
 *********************/

/* 
 * Compares whether two vectors are approximated from each other. 
 * If their sizes are not equal, return 0.
 */
int approx_v(struct vec*, struct vec*);

/* Add two vectors. */
struct vec vec_addition(struct vec*, struct vec*);

/* Multiply a scalar and a vector. */
struct vec scalar_vec_mult(double, struct vec*);

int is_point(struct vec*);
int is_vector(struct vec*);

#endif /* RMATH_VECTOR_H */
