#include "../bdd-for-c.h"
#include <math.h>

#include <raytracer/tuple.h>

#define CHECK_MACRO check(approx_v(&result, &expected));

spec("Tuple Arithmetic")
{
    tuple a1, a2, a3, a4, a5, a6;
    point(&a1, 3, -2, 5);
    vector(&a2, -2, 3, 1);

    point(&a3, 3, 2, 1);
    point(&a4, 5, 6, 7);
    vector(&a5, 5, 6, 7);
    vector(&a6, 3, 2, 1);

    it("Adding two tuples")
    {
        tuple result, expected;
        add_tuple(&a1, &a2, &result);
        point(&expected, 1, 1, 6);
        CHECK_MACRO
    }

    it("Subtracting two points.")
    {
        tuple result, expected;
        sub_tuple(&a3, &a4, &result);
        vector(&expected, -2, -4, -6);
        CHECK_MACRO
    }

    it("Subtracting a vector from a point.")
    {
        tuple result, expected;
        sub_tuple(&a3, &a5, &result);
        point(&expected, -2, -4, -6);
        CHECK_MACRO
    }

    it("Subtracting two vectors")
    {
        tuple result, expected;
        sub_tuple(&a6, &a5, &result);
        vector(&expected, -2, -4, -6);
        CHECK_MACRO
    }

    it("Subtracting a vector from the zero vector")
    {
        tuple zero, v, result, expected;
        vector(&zero, 0, 0, 0);
        vector(&v, 1, -2, 3);
        sub_tuple(&zero, &v, &result);
        vector(&expected, -1, 2, -3);
        CHECK_MACRO
    }

    it("Negating a tuple")
    {
        tuple a, result, expected;
        new_tuple4(&a, 1, -2, 3, -4);
        new_tuple4(&expected, -1, 2, -3, 4);
        
        negate_tuple(&a, &result);

        CHECK_MACRO
    }

    it("Multiplying a tuple by a scalar")
    {
        tuple a, result, expected;
        new_tuple4(&a, 1, -2, 3, -4);
        new_tuple4(&expected, 3.5, -7, 10.5, -14);
        mul_scalar_tuple(3.5, &a, &result);

        CHECK_MACRO
    }

    it("Multiplying a tuple by a fraction")
    {
        tuple a, result, expected;
        new_tuple4(&a, 1, -2, 3, -4);
        new_tuple4(&expected, 0.5, -1, 1.5, -2);
        mul_scalar_tuple(0.5, &a, &result);

        CHECK_MACRO
    }

    it("Dividing a tuple by a scalar")
    {
        tuple a, result, expected;
        new_tuple4(&a, 1, -2, 3, -4);
        new_tuple4(&expected, 0.5, -1, 1.5, -2);
        div_scalar_tuple(2, &a, &result);

        CHECK_MACRO
    }

    it("Computing the magnitude of vector (1, 0, 0)")
    {
        tuple v;
        vector(&v, 1, 0, 0);
        
        check(approx_d(magnitude(&v), 1));
    }

    it("Computing the magnitude of vector (0, 1, 0)")
    {
        tuple v;
        vector(&v, 0, 1, 0);
        
        check(approx_d(magnitude(&v), 1));
    }

    it("Computing the magnitude of vector (0, 0, 1)")
    {
        tuple v;
        vector(&v, 0, 0, 1);
        
        check(approx_d(magnitude(&v), 1));
    }

    it("Computing the magnitude of vector (1, 2, 3)")
    {
        tuple v;
        vector(&v, 1, 2, 3);
        check(approx_d(magnitude(&v), sqrt(14)));
    }

    it("Computing the magnitude of vector (-1, -2, -3)")
    {
        tuple v;
        vector(&v, -1, -2, -3);
        check(approx_d(magnitude(&v), sqrt(14)));
    }

    it("Normalizing vector (4, 0, 0) gives (1, 0, 0)")
    {
        tuple v, result, expected;
        vector(&v, 4, 0, 0);
        vector(&expected, 1, 0, 0);
        normalize(&v, &result);

        CHECK_MACRO
    }

    it("The magnitude of a normalized vector")
    {
        tuple v, normalized;
        vector(&v, 1, 2, 3);
        normalize(&v, &normalized);

        double m = magnitude(&normalized);

        check(approx_d(m, 1));
    }

    it("Normalizing vector (1, 2, 3)")
    {
        tuple v, result, expected;

        vector(&v, 1, 2, 3);
        normalize(&v, &result);
        vector(&expected, 1/sqrt(14), 2/sqrt(14), 3/sqrt(14));

        CHECK_MACRO
    }

    it("The dot product of two tuples.")
    {
        tuple a, b;
        vector(&a, 1, 2, 3);
        vector(&b, 2, 3, 4);

        double d = dot(&a, &b);

        check(approx_d(d, 20));
    }

    it("The cross product of two vectors.")
    {
        tuple a, b, result, expected;
        vector(&a, 1, 2, 3);
        vector(&b, 2, 3, 4);

        cross_product_4(&a, &b, &result);
        vector(&expected, -1, 2, -1);
        CHECK_MACRO

        cross_product_4(&b, &a, &result);
        vector(&expected, 1, -2, 1);
        CHECK_MACRO
    }
}