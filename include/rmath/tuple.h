#ifndef RMATH_TUPLE_H
#define RMATH_TUPLE_H


/* Compare whether two doubles are approx. */
int approx_d(double, double);

/* 
 * A vector is a fixed-size array of numbers closed under the following operations:
 * 1. Vector-to-vector addition
 * 2. Vector-to-scalar/scalar-to-vector multiplication.
 */
typedef struct tuple
{
    double *arr; /* Our implementation of a vector can only contain doubles. */
    int    size; /* How many elements are there in our vector. */
} tuple;

/*********************
 * VECTOR OPERATIONS *
 *********************/

/* 
 * Compares whether two vectors are approximated from each other. 
 * If their sizes are not equal, return 0.
 */
int approx_v(tuple*, tuple*);

/* Add two vectors. */
tuple tuple_addition(tuple*, tuple*, tuple*);

/* Multiply a scalar and a vector. */
tuple scalar_tuple_mult(double, tuple*, tuple*);

int is_point(tuple*);
int is_vector(tuple*);

void vector(tuple*, double, double, double);
void point(tuple*, double, double, double);
void new_tuple4(tuple*, double, double, double, double);

/* Some accessors for tuples of size 3 or 4. */
double _x(tuple*);
double _y(tuple*);
double _z(tuple*);
double _w(tuple*);

#endif /* RMATH_TUPLE_H */
