#include "../bdd_tap.h"

#include <raytracer/color.h>
#include <raytracer/raytracer_utils.h>

#define CHECK_MACRO check(c_approx(&result, &expected));

spec("Colors Tests")
{
    it("Colors are (red, green, blue) tuples.")
    {
        color c = new_color(-0.5, 0.4, 1.7);

        check(approx_d(c.red, -0.5));
        check(approx_d(c.green, 0.4));
        check(approx_d(c.blue, 1.7));
    }

    it("Adding colors")
    {
        color c1 = new_color(0.9, 0.6, 0.75);
        color c2 = new_color(0.7, 0.1, 0.25);
        color result = color_add(&c1, &c2);
        color expected = new_color(1.6, 0.7, 1.0);

        CHECK_MACRO
    }

    it("Subtracting colors")
    {
        color c1 = new_color(0.9, 0.6, 0.75);
        color c2 = new_color(0.7, 0.1, 0.25);
        color result = color_sub(&c1, &c2);
        color expected = new_color(0.2, 0.5, 0.5);
        CHECK_MACRO
    }

    it("Multipluing a color by a scalar")
    {
        color c = new_color(0.2, 0.3, 0.4);
        color result = color_mul(2, &c);
        color expected = new_color(0.4, 0.6, 0.8);
        CHECK_MACRO
    }

    it("Multiplying colors")
    {
        color c1 = new_color(1, 0.2, 0.4);
        color c2 = new_color(0.9, 1, 0.1);

        color result = color_hadamard(&c1, &c2);
        color expected = new_color(0.9, 0.2, 0.04);
        CHECK_MACRO
    }
}