#include "raytracer_utils.h"

#include <math.h>

/* An epsilon for approximated equality between two numbers. */
const double DEPSILON = 0.00001;

/* Compare doubles */
int approx_d(double a, double b)
{
    return fabs(a - b) < DEPSILON;
}