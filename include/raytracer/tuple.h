#ifndef RAYTRACER_TUPLE_H
#define RAYTRACER_TUPLE_H

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
int t_approx(tuple*, tuple*);

/* Add two vectors. */
tuple t_add(tuple* a, tuple* b);

/* Subtract two tuples. */
tuple t_sub(tuple* a, tuple* b);

/* Multiply a scalar and a vector. */
tuple t_mul(double a, tuple* v);

/* Divide a tuple by a scalar */
tuple t_div(double a, tuple* v);

/* Negate a tuple. */
tuple t_negate(tuple* v);

int is_point(tuple*);
int is_vector(tuple*);

tuple vector(double, double, double);
tuple point(double, double, double);
tuple new_tuple4(double, double, double, double);
tuple t_zeros(int size);

/* Compute the length of the vector, or magnitude. */
double magnitude(tuple* v);

/* Take an arbitrary vector and convert it into a unit vector */
tuple t_normalize(tuple* v);

/* Get the dot product of two tuples */
double t_dot(tuple* v, tuple* w);

/* Cross product of two tuples of size 4. */
tuple cross_product_4(tuple* v, tuple* w);

/* Hadamard Product of two tuples. */
tuple t_hadamard(tuple* v, tuple* w);

/* Some accessors for tuples of size 3 or 4. */
double _x(tuple*);
double _y(tuple*);
double _z(tuple*);
double _w(tuple*);

/* Print tuple. */
void t_print(tuple*);

/* Free the tuple. */
void t_free(tuple*);

#endif /* RAYTRACER_TUPLE_H */
