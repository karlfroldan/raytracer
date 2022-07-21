#include "matrix_transformations.h"
#include <math.h>

/* Create a translation matrix */
matrix translate(double x, double y, double z)
{
    matrix m = m_id(4);

    m_update_at(&m, 0, 3, x);
    m_update_at(&m, 1, 3, y);
    m_update_at(&m, 2, 3, z);

    return m;
}

/* Create a scaling matrix. */
matrix scale(double x, double y, double z)
{
    matrix m = m_id(4);

    m_update_at(&m, 0, 0, x);
    m_update_at(&m, 1, 1, y);
    m_update_at(&m, 2, 2, z);
    return m;
}

/* Rotate along an axis. */
matrix rotate(int axis, double theta)
{
    matrix m = m_id(4);

    double cos_r = cos(theta);
    double sin_r = sin(theta);

    if (axis == XAXIS)
    {
        m_update_at(&m, 1, 1, cos_r);
        m_update_at(&m, 1, 2, -sin_r);
        m_update_at(&m, 2, 1, sin_r);
        m_update_at(&m, 2, 2, cos_r);
    }
    else if (axis == YAXIS)
    {
        m_update_at(&m, 0, 0, cos_r);
        m_update_at(&m, 0, 2, sin_r);
        m_update_at(&m, 2, 0, -sin_r);
        m_update_at(&m, 2, 2, cos_r);
    }
    else 
    {
        m_update_at(&m, 0, 0, cos_r);
        m_update_at(&m, 0, 1, -sin_r);
        m_update_at(&m, 1, 0, sin_r);
        m_update_at(&m, 1, 1, cos_r);
    }
    
    return m;
}

/* Shearing transformation */
matrix shear(double x_y, double x_z, double y_x, double y_z, double z_x, double z_y)
{
    matrix m = m_id(4);

    m_update_at(&m, 0, 1, x_y);
    m_update_at(&m, 0, 2, x_z);
    
    m_update_at(&m, 1, 0, y_x);
    m_update_at(&m, 1, 2, y_z);

    m_update_at(&m, 2, 0, z_x);
    m_update_at(&m, 2, 1, z_y);

    return m;
}

/* Apply matrix transformation */
tuple apply(matrix m, tuple t) 
{
    return m_mul_tuple(&m, &t);
}

matrix chain(matrix a, matrix b)
{
    return m_mul(&b, &a);
}