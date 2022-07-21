#include <raytracer/matrix.h>

#include "../bdd-for-c.h"
#include <raytracer/raytracer_utils.h>

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
}