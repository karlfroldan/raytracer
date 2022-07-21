#include <raytracer/matrix.h>
#include <raytracer/matrix_transformations.h>

#include "../bdd-for-c.h"
#include <raytracer/raytracer_utils.h>

#include <math.h>

spec("Matrix Transformation Tests")
{
    it("Multiplying by a translation matrix")
    {
        matrix transform = translate(5, -3, 2);
        tuple p = point(-3, 4, 5);

        tuple r = m_mul_tuple(&transform, &p);
        tuple e = point(2, 1, 7);

        check(t_approx(&r, &e));
    }

    it("Multiplying by the inverse of a translation matrix")
    {
        matrix transform = translate(5, -3, 2);
        tuple p = point(-3, 4, 5);

        matrix inv = m_inverse(&transform);

        tuple r = m_mul_tuple(&inv, &p);
        tuple e = point(-8, 7, 3);

        check(t_approx(&r, &e));
    }

    it("Translation does not affect vectors")
    {
        matrix transform = translate(5, -3, 2);
        tuple p = vector(-3, 4, 5);

        tuple r = m_mul_tuple(&transform, &p);
        

        check(t_approx(&r, &p));
    }

    it("A scaling matrix applied to a point")
    {
        matrix transform = scale(2, 3, 4);
        tuple p = point(-4, 6, 8);
        tuple e = point(-8, 18, 32);

        tuple r = m_mul_tuple(&transform, &p);

        check(t_approx(&e, &r));
    }

    it("A scaling matrix applied to a vector")
    {
        matrix transform = scale(2, 3, 4);
        tuple p = vector(-4, 6, 8);
        tuple e = vector(-8, 18, 32);

        tuple r = m_mul_tuple(&transform, &p);

        check(t_approx(&e, &r));
    }

    it("Multiplying by the inverse of a scaling matrix")
    {
        matrix transform = scale(2, 3, 4);
        matrix inv = m_inverse(&transform);
        tuple p = vector(-4, 6, 8);
        tuple e = vector(-2, 2, 2);

        tuple r = m_mul_tuple(&inv, &p);

        check(t_approx(&e, &r));
    }

    it("Reflection is scaling by a negative value")
    {
        matrix transform = scale(-1, 1, 1);
        tuple p = point(2, 3, 4);
        tuple e = point(-2, 3, 4);

        tuple r = m_mul_tuple(&transform, &p);

        check(t_approx(&e, &r));
    }

    it("Rotating a point around the x axis")
    {
        matrix half_q = rotate(XAXIS, PI / 4);
        matrix full_q = rotate(XAXIS, PI / 2);

        tuple p = point(0, 1, 0);

        tuple hqp = m_mul_tuple(&half_q, &p);
        tuple fqp = m_mul_tuple(&full_q, &p);

        tuple e1 = point(0, sqrt(2)/2, sqrt(2)/2);
        tuple e2 = point(0, 0, 1);

        check(t_approx(&hqp, &e1));
        check(t_approx(&fqp, &e2));
    }

    it("The inverse of an x-rotation rotates in the opposite direction")
    {
        tuple p = point(0, 1, 0);

        matrix hqp = rotate(XAXIS, PI / 4);
        matrix inv = m_inverse(&hqp);
        tuple r = m_mul_tuple(&inv, &p);
        tuple e = point(0, sqrt(2)/ 2, -sqrt(2)/2);

        check(t_approx(&r, &e));
    }

    it("Rotating a point around the y axis")
    {
        matrix half_q = rotate(YAXIS, PI / 4);
        matrix full_q = rotate(YAXIS, PI / 2);

        tuple p = point(0, 0, 1);

        tuple hqp = m_mul_tuple(&half_q, &p);
        tuple fqp = m_mul_tuple(&full_q, &p);

        tuple e1 = point(sqrt(2)/2, 0, sqrt(2)/2);

        tuple e2 = point(1, 0, 0);

        check(t_approx(&hqp, &e1));
        check(t_approx(&fqp, &e2));
    }

    it("Rotating a point around the z axis")
    {
        matrix half_q = rotate(ZAXIS, PI / 4);
        matrix full_q = rotate(ZAXIS, PI / 2);

        tuple p = point(0, 1, 0);

        tuple hqp = m_mul_tuple(&half_q, &p);
        tuple fqp = m_mul_tuple(&full_q, &p);

        tuple e1 = point(-sqrt(2)/2, sqrt(2)/2, 0);
        tuple e2 = point(-1, 0, 0);

        check(t_approx(&hqp, &e1));
        check(t_approx(&fqp, &e2));
    }

    it("A shearing transformation moves x in proportion to y")
    {
        matrix transform = shear(1, 0, 0, 0, 0, 0);
        
        tuple p = point(2, 3, 4);
        tuple e = point(5, 3, 4);
        tuple r = m_mul_tuple(&transform, &p);

        check(t_approx(&r, &e));
    }

    it("A shearing transformation moves x in proportion to z")
    {
        matrix transform = shear(0, 1, 0, 0, 0, 0);
        
        tuple p = point(2, 3, 4);
        tuple e = point(6, 3, 4);
        tuple r = m_mul_tuple(&transform, &p);

        check(t_approx(&r, &e));
    }

    it("A shearing transformation moves y in proportion to x")
    {
        matrix transform = shear(0, 0, 1, 0, 0, 0);
        
        tuple p = point(2, 3, 4);
        tuple e = point(2, 5, 4);
        tuple r = m_mul_tuple(&transform, &p);

        check(t_approx(&r, &e));
    }

    it("A shearing transformation moves y in proportion to z")
    {
        matrix transform = shear(0, 0, 0, 1, 0, 0);
        
        tuple p = point(2, 3, 4);
        tuple e = point(2, 7, 4);
        tuple r = m_mul_tuple(&transform, &p);

        check(t_approx(&r, &e));
    }

    it("A shearing transformation moves z in proportion to x")
    {
        matrix transform = shear(0, 0, 0, 0, 1, 0);
        
        tuple p = point(2, 3, 4);
        tuple e = point(2, 3, 6);
        tuple r = m_mul_tuple(&transform, &p);

        check(t_approx(&r, &e));
    }

    it("A shearing transformation moves z in proportion to y")
    {
        matrix transform = shear(0, 0, 0, 0, 0, 1);
        
        tuple p = point(2, 3, 4);
        tuple e = point(2, 3, 7);
        tuple r = m_mul_tuple(&transform, &p);

        check(t_approx(&r, &e));
    }

    it("Individual transformations are applied in sequence")
    {
        tuple p = point(1, 0, 1);
        matrix a = rotate(XAXIS, PI / 2);
        matrix b = scale(5, 5, 5);
        matrix c = translate(10, 5, 7);

        // apply rotation first.
        tuple e = point(1, -1, 0);
        tuple r = m_mul_tuple(&a, &p);

        check(t_approx(&e, &r));

        // apply scaling.
        e = point(5, -5, 0);
        r = m_mul_tuple(&b, &r);

        check(t_approx(&e, &r));

        // apply translation
        e = point(15, 0, 7);
        r = m_mul_tuple(&c, &r);

        check(t_approx(&e, &r));
    }

    it("Chained transformations must be applied in reverse order.")
    {
        tuple p = point(1, 0, 1);
        matrix a = rotate(XAXIS, PI / 2);
        matrix b = scale(5, 5, 5);
        matrix c = translate(10, 5, 7);

        matrix t = m_mul(&c, &b);
        t = m_mul(&t, &a);

        tuple e = point(15, 0, 7);
        tuple r = m_mul_tuple(&t, &p);

        check(t_approx(&e, &r));
    }

    it("Using `chain` does not need reverse order application.")
    {
        tuple p = point(1, 0, 1);
        matrix a = rotate(XAXIS, PI / 2);
        matrix b = scale(5, 5, 5);
        matrix c = translate(10, 5, 7);

        matrix t = chain(chain(a, b), c);
        tuple e = point(15, 0, 7);
        tuple r = apply(t, p);
        check(t_approx(&e, &r));
    }
}