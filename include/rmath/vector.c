#include "vector.h"
#include <math.h> /* For fabs */

#define TRUE  1
#define FALSE 0

/* Compare doubles */
int approx_d(double a, double b)
{
    return fabs(a - b) < EPSILON;
}

int approx_v(struct vec* v1, struct_vec* v2)
{
    /* Return false if their sizes are not equal */
    if (v1->size != v2->size)
        return FALSE;

    int n = v1->size;
    bool is_approx = TRUE;

    for (int i = 0; i < n; ++i)
        is_approx = is_approx && approx_d(v1->arr[i], v2->arr[i]);
    return is_approx;
}
