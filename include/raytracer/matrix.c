#include "matrix.h"
#include <stdio.h>

/* Instantiate a new matrix.
The input is a list of values in row-major order.
If the list is shorter than 16 values, then the 
others will be filled with 0s. 
*/
matrix m_new(double* vals, int n, int dims) 
{
    tuple rs[4];

    int p = 0;

    for (int i = 0; i < 4; ++i) 
        rs[i] = ZERO_T;

    for (int i = 0; i < n; ++i)
    {
        /* Which tuple? */
        int k = i / dims;
        /* Which index? */
        int j = i % dims;

        if (j == 0)
            rs[k].x = vals[i];
        else if (j == 1)
            rs[k].y = vals[i];
        else if (j == 2)
            rs[k].z = vals[i];
        else
            rs[k].w = vals[i];
        p++;
    }

    for (; p < dims * dims; ++p)
    {
        /* Which tuple? */
        int k = p / dims;
        /* Which index? */
        int j = p % dims;

        if (j == 0)
            rs[k].x = 0;
        else if (j == 1)
            rs[k].y = 0;
        else if (j == 2)
            rs[k].z = 0;
        else
            rs[k].w = 0;
        p++;
    }

    matrix m = {rs[0], rs[1], rs[2], rs[3], dims};
    return m;
}

/* Create a 2x2 matrix. */
matrix m_2(double* vals, int n)
{
    matrix m = m_new(vals, n, 2);
    m.dims = 2;

    return m;
}

/* Create a 3x3 matrix. */
matrix m_3(double* vals, int n)
{
    matrix m = m_new(vals, n, 3);
    m.dims = 3;
    return m;
}

/* Create a 4x4 matrix. */
matrix m_4(double* vals, int n)
{
    matrix m = m_new(vals, n, 4);
    m.dims = 3;
    return m;
}

/* 
 * Compares whether two matrices are approximated from each other. 
 * If their sizes are not equal, return 0.
 */
int m_approx(matrix* m, matrix* n)
{
    return t_approx(&(m->r1), &(n->r1)) && t_approx(&(m->r2), &(n->r2)) && 
        t_approx(&(m->r3), &(n->r3)) && t_approx(&(m->r4), &(m->r4));
}

/* Get the value of the matrix at some coordinate */
double m_at(matrix* m, int x, int y) 
{
    if (x == 0)
    {
        if (y == 0)
            return m->r1.x;
        else if (y == 1)
            return m->r1.y;
        else if (y == 2)
            return m->r1.z;
        else if (y == 3)
            return m->r1.w;
    }
    else if (x == 1)
    {
        if (y == 0)
            return m->r2.x;
        else if (y == 1)
            return m->r2.y;
        else if (y == 2)
            return m->r2.z;
        else if (y == 3)
            return m->r2.w;
    }
    else if (x == 2)
    {
        if (y == 0)
            return m->r3.x;
        else if (y == 1)
            return m->r3.y;
        else if (y == 2)
            return m->r3.z;
        else if (y == 3)
            return m->r3.w;
    }
    else if (x == 3) 
    {
        if (y == 0)
            return m->r4.x;
        else if (y == 1)
            return m->r4.y;
        else if (y == 2)
            return m->r4.z;
        else if (y == 3)
            return m->r4.w;
    }

    fprintf(stderr, "index out of bounds\n");

    return 0.0;
}

/* Print the matrix. */
void m_print(matrix* m)
{
    if (m->dims == 2)
    {
        printf("%3.3f %3.3f\n", m->r1.x, m->r1.y);
        printf("%3.3f %3.3f\n", m->r2.x, m->r2.y);
    }
    else if (m->dims == 3)
    {
        printf("%3.3f %3.3f %3.3f\n", m->r1.x, m->r1.y, m->r1.z);
        printf("%3.3f %3.3f %3.3f\n", m->r2.x, m->r2.y, m->r2.z);
    }
    else 
    {
        printf("%3.3f %3.3f %3.3f %3.3f\n", m->r1.x, m->r1.y, m->r1.z, m->r1.w);
        printf("%3.3f %3.3f %3.3f %3.3f\n", m->r2.x, m->r2.y, m->r2.z, m->r2.w);
        printf("%3.3f %3.3f %3.3f %3.3f\n", m->r3.x, m->r3.y, m->r3.z, m->r3.w);
        printf("%3.3f %3.3f %3.3f %3.3f\n", m->r4.x, m->r4.y, m->r4.z, m->r4.w);
    }
        
    
}