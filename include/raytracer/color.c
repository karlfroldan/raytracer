#include "color.h"

#include "raytracer_utils.h"

/* Create a new color given the RGB values. */
color new_color(double red, double green, double blue)
{
    color c = {
        red, green, blue
    };

    return c;
}

/* Add two colors. */
color color_add(color* c1, color* c2)
{
    color c = {
        c1->red + c2->red,
        c1->green + c2->green,
        c1->blue + c2->blue
    };

    return c;
}

/* Subtract two colors. */
color color_sub(color* c1, color* c2)
{
    color c = {
        c1->red - c2->red,
        c1->green - c2->green,
        c1->blue - c2->blue
    };

    return c;
}

/* Multiply two colors by scalar */
color color_mul(double c, color* c2)
{
    color c3 = {
        c * c2->red,
        c * c2->green,
        c * c2->blue
    };

    return c3;
}

/* Calculate the hadamard product of colors */
color color_hadamard(color* c1, color* c2)
{
    color c3 = {
        c1->red * c2->red,
        c1->green * c2->green,
        c1->blue * c2->blue
    };

    return c3;
}

/* Approximated equality between two colors. */
int c_approx(color* c1, color* c2)
{
    return 
        approx_d(c1->red, c2->red) && 
        approx_d(c1->green, c2->green) && 
        approx_d(c1->blue, c2->blue);
}