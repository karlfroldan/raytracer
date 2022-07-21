#include "matrix.h"
#include <stdio.h>

/* Create a zero matrix of some dimension. */
matrix m_zero(int dims)
{
    matrix m = {
        ZERO_T, ZERO_T, ZERO_T, ZERO_T, dims
    };

     return m;
}

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
    m.dims = 4;
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

/* Change the value of the matrix at */
void m_update_at(matrix* m, int x, int y, double v)
{
    if (x == 0)
    {
        if (y == 0)
            m->r1.x = v;
        else if (y == 1)
            m->r1.y = v;
        else if (y == 2)
            m->r1.z = v;
        else if (y == 3)
            m->r1.w = v;
    }
    else if (x == 1)
    {
        if (y == 0)
            m->r2.x = v;
        else if (y == 1)
            m->r2.y = v;
        else if (y == 2)
            m->r2.z = v;
        else if (y == 3)
            m->r2.w = v;
    }
    else if (x == 2)
    {
        if (y == 0)
            m->r3.x = v;
        else if (y == 1)
            m->r3.y = v;
        else if (y == 2)
            m->r3.z = v;
        else if (y == 3)
            m->r3.w = v;
    }
    else if (x == 3) 
    {
        if (y == 0)
            m->r4.x = v;
        else if (y == 1)
            m->r4.y = v;
        else if (y == 2)
            m->r4.z = v;
        else if (y == 3)
            m->r4.w = v;
    }
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

/* Multiply two matrices. */
matrix m_mul(matrix* a, matrix* b)
{
    int n = a->dims;

    matrix m = m_zero(n);

    /* iterate through rows of a */
    for (int i = 0; i < n; ++i)
    {
        /* iterate through columns of b */
        for (int j = 0; j < n; ++j)
        {
            double v = 0.0;
            /* iterate through columns of a */
            for (int k = 0; k < n; ++k)
            {
                v += m_at(a, i, k) * m_at(b, k, j);
            }
            m_update_at(&m, i, j, v);
        }
    }

    return m;
}

/* Matrix multiplied by a tuple. */
tuple m_mul_tuple(matrix* m, tuple* a)
{
    tuple b = ZERO_T;

    /* Iterate through rows of m */
    for (int i = 0; i < m->dims; ++i)
    {
        double v = 0.0;

        /* iterate through columns of m */
        for (int j = 0; j < m->dims; ++j)
        {
            double w;

            if (j == 0)
                w = a->x;
            else if (j == 1)
                w = a->y;
            else if (j == 2)
                w = a->z;
            else 
                w = a->w;

            v += m_at(m, i, j) * w;
        }

        if (i == 0)
            b.x = v;
        else if (i == 1)
            b.y = v;
        else if (i == 2)
            b.z = v;
        else 
            b.w = v;
    }

    return b;
}

/* Identity matrix */
matrix m_id(int dim)
{
    if (dim == 2)
    {
        double vals[4] = {
            1, 0, 0, 1
        };
        return m_2(vals, 4);
    }
    else if (dim == 3)
    {
        double vals[9] = {
            1, 0, 0,
            0, 1, 0,
            0, 0, 1
        };

        return m_3(vals, 9);
    }
    else if (dim == 4) 
    {
        double vals[16] = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        };

        return m_4(vals, 16);
    }

    return m_zero(4);
}

/* Matrix transpose  */
matrix transpose(matrix* m) 
{
    matrix a = m_zero(m->dims);

    for (int i = 0; i < m->dims; ++i)
    {
        for (int j = 0; j < m->dims; ++j)
        {
            m_update_at(&a, j, i, m_at(m, i, j));
        }
    }

    return a;
}