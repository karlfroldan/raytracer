#ifndef RAYTRACER_TUPLE_H
#define RAYTRACER_TUPLE_H

#define ZERO_T t_new(0.0, 0.0, 0.0, 0.0)

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

/* Instantiate a new tule. */
tuple t_new(double x, double y, double z, double w);

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

/* Print tuple. */
void t_print(tuple*);

#endif /* RAYTRACER_TUPLE_H */
