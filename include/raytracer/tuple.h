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
void add_tuple(tuple* a, tuple* b, tuple* result);

/* Subtract two tuples. */
void sub_tuple(tuple* a, tuple* b, tuple* result);

/* Multiply a scalar and a vector. */
void mul_scalar_tuple(double a, tuple* v, tuple* result);

/* Divide a tuple by a scalar */
void div_scalar_tuple(double a, tuple* v, tuple* result);

/* Negate a tuple. */
void negate_tuple(tuple* v, tuple* result);

int is_point(tuple*);
int is_vector(tuple*);

void vector(tuple*, double, double, double);
void point(tuple*, double, double, double);
void new_tuple4(tuple*, double, double, double, double);

/* Compute the length of the vector, or magnitude. */
double magnitude(tuple* v);

/* Take an arbitrary vector and convert it into a unit vector */
void normalize(tuple* v, tuple* result);

/* Get the dot product of two tuples */
double dot(tuple* v, tuple* w);

/* Cross product of two tuples of size 4. */
void cross_product_4(tuple* v, tuple* w, tuple* result);

/* Some accessors for tuples of size 3 or 4. */
double _x(tuple*);
double _y(tuple*);
double _z(tuple*);
double _w(tuple*);

#endif /* RMATH_TUPLE_H */
