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
tuple add_tuple(tuple* a, tuple* b);

/* Subtract two tuples. */
tuple sub_tuple(tuple* a, tuple* b);

/* Multiply a scalar and a vector. */
tuple mul_scalar_tuple(double a, tuple* v);

/* Divide a tuple by a scalar */
tuple div_scalar_tuple(double a, tuple* v);

/* Negate a tuple. */
tuple negate_tuple(tuple* v);

int is_point(tuple*);
int is_vector(tuple*);

tuple vector(double, double, double);
tuple point(double, double, double);
tuple new_tuple4(double, double, double, double);

/* Compute the length of the vector, or magnitude. */
double magnitude(tuple* v);

/* Take an arbitrary vector and convert it into a unit vector */
tuple normalize(tuple* v);

/* Get the dot product of two tuples */
double dot(tuple* v, tuple* w);

/* Cross product of two tuples of size 4. */
tuple cross_product_4(tuple* v, tuple* w);

/* Some accessors for tuples of size 3 or 4. */
double _x(tuple*);
double _y(tuple*);
double _z(tuple*);
double _w(tuple*);

#endif /* RMATH_TUPLE_H */
