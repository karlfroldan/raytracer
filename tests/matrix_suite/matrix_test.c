#include <raytracer/matrix.h>
#include <raytracer/matrix_transformations.h>

#include "../bdd-for-c.h"
#include <raytracer/raytracer_utils.h>

#include <math.h>

#define PI 3.14159265359

spec("Matrix tests")
{
    it("Constructing and inspecting a 4x4 matrix")
    {
        double vals[15] = {
            1, 2, 3, 4,
            5.5, 6.5, 7.5, 8.5,
            9, 10, 11, 12,
            13.5, 14.5, 15.5
        };

        matrix m = m_4(vals, 15);

        check(approx_d(m_at(&m, 0, 0), 1));
        check(approx_d(m_at(&m, 0, 3), 4));
        check(approx_d(m_at(&m, 1, 0), 5.5));
        check(approx_d(m_at(&m, 1, 2), 7.5));
        check(approx_d(m_at(&m, 2, 2), 11));
        check(approx_d(m_at(&m, 3, 0), 13.5));
        check(approx_d(m_at(&m, 3, 2), 15.5));
        check(approx_d(m_at(&m, 3, 3), 0));
    }

    it("A 2x2 matrix should be representable")
    {
        double vals[4] = {
            -3, 5, 
            1, -2
        };

        matrix m = m_2(vals, 4);

        check(approx_d(m_at(&m, 0, 0), -3));
        check(approx_d(m_at(&m, 0, 1), 5));
        check(approx_d(m_at(&m, 1, 0), 1));
        check(approx_d(m_at(&m, 1, 1), -2));
    }

    it("A 3x3 matrix should be representable")
    {
        double vals[9] = {
            -3, 5, 0,
            1, -2, -7,
            0, 1, 1
        };

        matrix m = m_3(vals, 9);

        check(approx_d(m_at(&m, 0, 0), -3));
        check(approx_d(m_at(&m, 1, 1), -2));
        check(approx_d(m_at(&m, 2, 2), 1));
    }

    it("Multiplying two matrices")
    {
        double vals_a[16] = {
            1, 2, 3, 4,
            5, 6, 7, 8,
            9, 8, 7, 6,
            5, 4, 3, 2
        };

        double vals_b[16] = {
            -2, 1, 2, 3,
            3, 2, 1, -1,
            4, 3, 6, 5,
            1, 2, 7, 8
        };

        double expected[16] = {
            20, 22, 50, 48,
            44, 54, 114, 108,
            40, 58, 110, 102,
            16, 26, 46, 42
        };

        matrix a = m_4(vals_a, 16);
        matrix b = m_4(vals_b, 16);
        matrix r = m_4(expected, 16);

        matrix result = m_mul(&a, &b);
        check(m_approx(&result, &r));
    }

    it("Matrix multiplied by a tuple")
    {
        double vals[16] = {
            1, 2, 3, 4, 
            2, 4, 4, 2, 
            8, 6, 4, 1,
            0, 0, 0, 1
        };

        matrix m = m_4(vals, 16);
        tuple a = point(1, 2, 3);
        tuple e = point(18, 24, 33);

        tuple r = m_mul_tuple(&m, &a);

        check(t_approx(&e, &r));
    }

    it("Multiplying a matrix by the identity matrix.")
    {
        double vals[16] = {
            0, 1, 2, 4,
            1, 2, 4, 8,
            2, 4, 8, 16,
            4, 8, 16, 32
        };

        matrix m = m_4(vals, 16);
        matrix id = m_id(4);

        matrix r = m_mul(&m, &id);

        check(m_approx(&m, &r));
    }

    it("Transposing a matrix")
    {
        double vals[16] = {
            0, 9, 3, 0,
            9, 8, 0, 8,
            1, 8, 5, 3,
            0, 0, 5, 8
        };

        double exps[16] = {
            0, 9, 1, 0,
            9, 8, 8, 0,
            3, 0, 5, 5,
            0, 8, 3, 8
        };

        matrix a = m_4(vals, 16);
        matrix e = m_4(exps, 16);
        matrix r = transpose(&a);

        check(m_approx(&r, &e));
    }

    it("Transposing the identity matrix.")
    {
        matrix m = m_id(4);
        matrix r = transpose(&m);

        check(m_approx(&m, &r));
    }

    it("Calculating the determinant of a 2x2 matrix")
    {
        double vals[4] = {
            1, 5, -3, 2
        };

        matrix m = m_2(vals, 4);
        double r = det(&m);

        check(approx_d(r, 17.0));
    }

    it("A submatrix of a 3x3 matrix is a 2x2 matrix")
    {
        double vals[9] = {
            1, 5, 0,
            -3, 2, 7,
            0, 6, -3
        };

        double exps[4] = {
            -3, 2, 
            0, 6
        };

        matrix m = m_3(vals, 9);
        matrix e = m_2(exps, 4);

        matrix r = submatrix(&m, 0, 2);

        check(m_approx(&r, &e));
    }

    it("A submatrix of a 4x4 matrix is a 3x3 matrix")
    {
        double vals[16] = {
            -6, 1, 1, 6,
            -8, 5, 8, 6,
            -1, 0, 8, 2,
            -7, 1, -1, 1
        };

        double exps[9] = {
            -6, 1, 6,
            -8, 8, 6,
            -7, -1, 1
        };

        matrix m = m_4(vals, 16);
        matrix e = m_3(exps, 9);

        matrix r = submatrix(&m, 2, 1);

        check(m_approx(&r, &e));
    }

    it("Calculating the minor of a 3x3 matrix.")
    {
        double vals[9] = {
            3, 5, 0,
            2, -1, -7,
            6, -1, 5
        };

        matrix a = m_3(vals, 9);

        matrix b = submatrix(&a, 1, 0);

        double db = det(&b);
        double minor_ = minor(&a, 1, 0);

        check(approx_d(db, minor_));
    }

    it("Calculating the cofactor of a 3x3 matrix")
    {
        double vals[9] = {
            3, 5, 0,
            2, -1, -7,
            6, -1, 5
        };

        matrix a = m_3(vals, 9);

        double m1 = minor(&a, 0, 0);
        double c1 = cofactor(&a, 0, 0);
        double m2 = minor(&a, 1, 0);
        double c2 = cofactor(&a, 1, 0);

        check(approx_d(m1, -12));
        check(approx_d(c1, -12));
        check(approx_d(m2, 25));
        check(approx_d(c2, -25));
    }

    it("Calculating the determinant of a 3x3 matrix")
    {
        double vals[9] = {
            1, 2, 6,
            -5, 8, -4,
            2, 6, 4
        };

        matrix a = m_3(vals, 9);

        double c1 = cofactor(&a, 0, 0);
        double c2 = cofactor(&a, 0, 1);
        double c3 = cofactor(&a, 0, 2);

        double d = det(&a);

        check(approx_d(c1, 56));
        check(approx_d(c2, 12));
        check(approx_d(c3, -46));
        check(approx_d(d, -196));
    }

    it("Calculating the determinant of a 4x4 matrix")
    {
        double vals[16] = {
            -2, -8, 3, 5,
            -3, 1, 7, 3,
            1, 2, -9, 6,
            -6, 7, 7, -9
        };

        matrix a = m_4(vals, 16);

        double c1 = cofactor(&a, 0, 0);
        double c2 = cofactor(&a, 0, 1);
        double c3 = cofactor(&a, 0, 2);
        double c4 = cofactor(&a, 0, 3);

        double d = det(&a);

        printf("%f\n", d);

        check(approx_d(c1, 690));
        check(approx_d(c2, 447));
        check(approx_d(c3, 210));
        check(approx_d(c4, 51))
        check(approx_d(d, -4071));
    }

    it("Testing an invertible matrix for invertibility")
    {
        double vals[16] = {
            6, 4, 4, 4,
            5, 5, 7, 6,
            4, -9, 3, -7,
            9, 1, 7, -6
        };

        matrix m = m_4(vals, 16);
        double d = det(&m);

        check(approx_d(d, -2120));
        check(is_invertible(&m));
    }

    it("Testing a non-invertible matrix for invertibility")
    {
        double vals[16] = {
            -4, 2, -2, -3,
            9, 6, 2, 6,
            0, -5, 1, -5,
            0, 0, 0, 0
        };

        matrix m = m_4(vals, 16);
        double d = det(&m);

        check(approx_d(d, 0));
        check(!is_invertible(&m));
    }

    it("Calculating the inverse of a matrix")
    {
        double vals[16] = {
            -5, 2, 6, -8,
            1, -5, 1, 8,
            7, 7, -6, -7,
            1, -3, 7, 4
        };

        double exps[16] = {
            0.21805, 0.45113, 0.24060, -0.04511,
            -0.80827, -1.45677, -0.44361, 0.52068,
            -0.07895, -0.22368, -0.05263, 0.19737,
            -0.52256, -0.81391, -0.30075, 0.30639
        };

        matrix m = m_4(vals, 16);
        matrix e = m_4(exps, 16);
        matrix b = m_inverse(&m);

        double d = det(&m);
        double c1 = cofactor(&m, 2, 3);
        double c2 = cofactor(&m, 3, 2);

        check(approx_d(d, 532));
        check(approx_d(c1, -160));
        //check(approx_d(m_at(&b, 3, 2), -160/532));
        check(approx_d(c2, 105));
        //check(approx_d(m_at(&b, 2, 3), 105/532));
        check(m_approx(&b, &e));
    }

    it("Calculating the inverse of another matrix")
    {
        double vals[16] = {
            8, -5, 9, 2,
            7, 5, 6, 1,
            -6, 0, 9, 6,
            -3, 0, -9, -4
        };

        double exps[16] = {
            -0.15385, -0.15385, -0.28205, -0.53846,
            -0.07692, 0.12308, 0.02564, 0.03077,
            0.35897, 0.35897, 0.43590, 0.92308,
            -0.69231, -0.69231, -0.76923, -1.92308
        };

        matrix m = m_4(vals, 16);
        matrix e = m_4(exps, 16);
        matrix b = m_inverse(&m);


        check(m_approx(&b, &e));
    }
    it("Calculating the inverse of a third matrix")
    {
        double vals[16] = {
            9, 3, 0, 9,
            -5, -2, -6, -3,
            -4, 9, 6, 4,
            -7, 6, 6, 2
        };

        double exps[16] = {
            -0.04074, -0.07778, 0.14444, -0.22222,
            -0.07778, 0.03333, 0.36667, -0.33333,
            -0.02901, -0.14630, -0.10926, 0.12963,
            0.17778, 0.06667, -0.26667, 0.33333
        };

        matrix m = m_4(vals, 16);
        matrix e = m_4(exps, 16);
        matrix b = m_inverse(&m);


        check(m_approx(&b, &e));
    }

    it("Multiplying a product by its inverse")
    {
        double vals_a[16] = {
            3, -9, 7, 3,
            3, -8, 2, -9,
            -4, 4 , 4, 1,
            -6, 5, -1, 1
        };

        double vals_b[16] = {
            8, 2, 2, 2,
            3, -1, 7, 0,
            7, 0, 5, 4,
            6, -2, 0, 5
        };

        matrix a = m_4(vals_a, 16);
        matrix b = m_4(vals_b, 16);

        matrix c = m_mul(&a, &b);

        matrix inv_b = m_inverse(&b);
        matrix inv_c = m_mul(&c, &inv_b);

        check(m_approx(&inv_c, &a));
    }

}