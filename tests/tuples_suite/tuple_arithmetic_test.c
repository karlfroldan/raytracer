#include "../bdd-for-c.h"
#include <rmath/tuple.h>

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
}