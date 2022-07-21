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
}