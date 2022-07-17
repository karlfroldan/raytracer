#include "tuple.h"
#include <math.h> /* For fabs */
#include <stdlib.h>
#include <assert.h>

#define TRUE  1
#define FALSE 0

/* An epsilon for approximated equality between two numbers. */
const double DEPSILON = 0.00001;

/* Reset a tuple. */
void t_reset(tuple* v)
{
    if (v->size > 0)
    {
        v->size = 0;
        free(v->arr);
    } 
}

void t_init(tuple* v, int size)
{
    v->size = size;
    v->arr = malloc(sizeof(double) * size);
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int min(int a, int b)
{
    return (a > b) ? b : a;
}

/* Compare doubles */
int approx_d(double a, double b)
{
    return fabs(a - b) < DEPSILON;
}

/* Compare vectors. */ 
int approx_v(tuple* v1, tuple* v2)
{
    /* Return false if their sizes are not equal */
    if (v1->size != v2->size)
        return FALSE;

    int n = v1->size;
    int is_approx = TRUE;

    for (int i = 0; i < n; ++i)
        is_approx = is_approx && approx_d(v1->arr[i], v2->arr[i]);
    return is_approx;
}

/* Add two vectors. */
void 
add_tuple(tuple* a, tuple* b, tuple* result) 
{
    int n = min(a->size, b->size); 

    t_reset(result);
    t_init(result, n);

    for (int i = 0; i < n; ++i)
        result->arr[i] = a->arr[i] + b->arr[i];
}

void
sub_tuple(tuple* a, tuple* b, tuple* r) 
{
    int n = min(a->size, b->size); 

    t_reset(r);
    t_init(r, n);

    for (int i = 0; i < n; ++i)
        r->arr[i] = a->arr[i] - b->arr[i];
}

/* Multiply a scalar and a vector. */
void
mul_scalar_tuple(double a, tuple* v, tuple* result) 
{
    t_reset(result);
    t_init(result, v->size);

    for (int i = 0; i < v->size; ++i) 
        result->arr[i] = a * v->arr[i];
}

/* Divide a tuple by a scalar. */
void 
div_scalar_tuple(double a, tuple* v, tuple* result)
{
    t_reset(result);
    t_init(result, v->size);

    for (int i = 0; i < v->size; ++i)
        result->arr[i] = v->arr[i] / a;
}

/* Negate a tuple. */
void 
negate_tuple(tuple* v, tuple* result) 
{
    t_reset(result);
    t_init(result, v->size);

    for (int i = 0; i < v->size; ++i)
        result->arr[i] = -1 * v->arr[i];
}

int
is_point(tuple* v) 
{
    return v->size == 4 && approx_d(v->arr[3], 1);
}

int 
is_vector(tuple *v) 
{
    return v->size == 4 && approx_d(v->arr[3], 0);
}

void vector(tuple* v, double a, double b, double c)
{
    v->arr = malloc(sizeof(double) * 4);
    v->arr[0] = a;
    v->arr[1] = b;
    v->arr[2] = c;
    v->arr[3] = 0.0;
    v->size = 4;
}

void point(tuple* v, double a, double b, double c)
{
    v->arr = malloc(sizeof(double) * 4);
    v->arr[0] = a;
    v->arr[1] = b;
    v->arr[2] = c;
    v->arr[3] = 1.0;
    v->size = 4;
}

void new_tuple4(tuple* v, double a, double b, double c, double d)
{
    v->arr = malloc(sizeof(double) * 4);
    v->arr[0] = a;
    v->arr[1] = b;
    v->arr[2] = c;
    v->arr[3] = d;
    v->size = 4;
}

double _x(tuple* t)
{
    if (t->size >= 1)
        return t->arr[0];
    return 0;
}

double _y(tuple* t)
{
    if (t->size >= 2)
        return t->arr[1];
    return 0;
}

double _z(tuple* t)
{
    if (t->size >= 3)
        return t->arr[2];
    return 0;
}

double _w(tuple* t)
{
    if (t->size >= 4)
        return t->arr[3];
    return 0;
}

/* Compute the length of the vector, or magnitude. */
double
magnitude(tuple* v)
{
    double magnitude = 0.0;

    for (int i = 0; i < v->size; ++i)
        magnitude += pow(v->arr[i], 2);

    return sqrt(magnitude);
}

/* Take an arbitrary vector and convert it into a unit vector */
void 
normalize(tuple* v, tuple* result)
{
    double m = magnitude(v);

    t_reset(result);
    t_init(result, v->size);

    for (int i = 0; i < v->size; ++i) 
        result->arr[i] = v->arr[i] / m;
}

/* Get the dot product of two tuples */
double 
dot(tuple* v, tuple* w)
{
    double d = 0.0;

    int n = min(v->size, w->size);

    for(int i = 0; i < n; ++i)
        d += v->arr[i] * w->arr[i];

    return d;
}


/* Take an arbitrary vector and convert it into a unit vector */
void 
cross_product_4(tuple* a, tuple* b, tuple* result)
{
    t_reset(result);
    t_init(result, 4);

    assert(a->size == 4);
    assert(b->size == 4);
    assert(is_vector(a));
    assert(is_vector(b));

    vector(result, 
        _y(a) * _z(b) - _z(a) * _y(b),
        _z(a) * _x(b) - _x(a) * _z(b),
        _x(a) * _y(b) - _y(a) * _x(b)
    );
}