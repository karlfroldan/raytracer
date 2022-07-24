#include "../bdd_tap.h"
#include <math.h>

#include <raytracer/tuple.h>
#include <raytracer/raytracer_utils.h>

#define CHECK_MACRO check(t_approx(&result, &expected));

spec("Tuple Arithmetic")
{
    it("Adding two tuples")
    {
        tuple a1 = point(3, -2, 5);
        tuple a2 = vector(-2, 3, 1);

        tuple result = t_add(&a1, &a2);
        tuple expected = point(1, 1, 6);
        CHECK_MACRO
    }

    it("Subtracting two points.")
    {
        tuple a3 = point(3, 2, 1);
        tuple a4 = point(5, 6, 7);
        tuple result = t_sub(&a3, &a4);
        tuple expected = vector(-2, -4, -6);
        CHECK_MACRO
    }

    it("Subtracting a vector from a point.")
    {
        tuple a3 = point(3, 2, 1);
        tuple a5 = vector(5, 6, 7);
        tuple result = t_sub(&a3, &a5);
        tuple expected = point(-2, -4, -6);
        CHECK_MACRO
    }

    it("Subtracting two vectors")
    {
        tuple a5 = vector(5, 6, 7);
        tuple a6 = vector(3, 2, 1);

        tuple result = t_sub(&a6, &a5);

        tuple expected = vector(-2, -4, -6);
        CHECK_MACRO
    }

    it("Subtracting a vector from the zero vector")
    {
        tuple zero = ZERO_T;
        tuple v = vector(1, -2, 3);
        tuple result = t_sub(&zero, &v);

        tuple expected = vector(-1, 2, -3);
        CHECK_MACRO
    }

    it("Negating a tuple")
    {
        tuple a = t_new(1, -2, 3, -4);
        tuple expected = t_new(-1, 2, -3, 4);
        tuple result = t_negate(&a);

        CHECK_MACRO
    }

    it("Multiplying a tuple by a scalar")
    {
        tuple a = t_new(1, -2, 3, -4);
        tuple expected = t_new(3.5, -7, 10.5, -14);
        tuple result = t_mul(3.5, &a);

        CHECK_MACRO
    }

    it("Multiplying a tuple by a fraction")
    {
        tuple a = t_new(1, -2, 3, -4);
        tuple expected = t_new(0.5, -1, 1.5, -2);
        tuple result = t_mul(0.5, &a);

        CHECK_MACRO
    }

    it("Dividing a tuple by a scalar")
    {
        tuple a = t_new(1, -2, 3, -4);
        tuple expected = t_new(0.5, -1, 1.5, -2);
        tuple result = t_div(2, &a);

        CHECK_MACRO
    }

    it("Computing the magnitude of vector (1, 0, 0)")
    {
        tuple v = vector(1, 0, 0);
        
        check(approx_d(magnitude(&v), 1));
    }

    it("Computing the magnitude of vector (0, 1, 0)")
    {
        tuple v = vector(0, 1, 0);
        
        check(approx_d(magnitude(&v), 1));
    }

    it("Computing the magnitude of vector (0, 0, 1)")
    {
        tuple v = vector(0, 0, 1);
        
        check(approx_d(magnitude(&v), 1));
    }

    it("Computing the magnitude of vector (1, 2, 3)")
    {
        tuple v = vector(1, 2, 3);
        check(approx_d(magnitude(&v), sqrt(14)));
    }

    it("Computing the magnitude of vector (-1, -2, -3)")
    {
        tuple v = vector(-1, -2, -3);
        check(approx_d(magnitude(&v), sqrt(14)));
    }

    it("Normalizing vector (4, 0, 0) gives (1, 0, 0)")
    {
        tuple v = vector(4, 0, 0);
        tuple expected = vector(1, 0, 0);
        tuple result = t_normalize(&v);

        CHECK_MACRO
    }

    it("The magnitude of a normalized vector")
    {
        tuple v = vector(1, 2, 3);
        tuple result = t_normalize(&v);

        double m = magnitude(&result);

        check(approx_d(m, 1));
    }

    it("Normalizing vector (1, 2, 3)")
    {
        tuple v = vector(1, 2, 3);
        tuple expected = vector(1/sqrt(14), 2/sqrt(14), 3/sqrt(14));
        tuple result = t_normalize(&v);

        CHECK_MACRO
    }

    it("The dot product of two tuples.")
    {
        tuple a = vector(1, 2, 3);
        tuple b = vector(2, 3, 4);

        double d = t_dot(&a, &b);

        check(approx_d(d, 20));
    }

    it("The cross product of two vectors.")
    {
        tuple result, expected;
        tuple a = vector(1, 2, 3);
        tuple b = vector(2, 3, 4);

        result = cross_product_4(&a, &b);
        expected = vector(-1, 2, -1);

        CHECK_MACRO


        result = cross_product_4(&b, &a);
        expected = vector(1, -2, 1);
        CHECK_MACRO
    }
}