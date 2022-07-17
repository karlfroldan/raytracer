#ifndef RAYTRACER_COLOR_H
#define RAYTRACER_COLOR_H

#define BLACK new_color(0.0, 0.0, 0.0)
#define RED   new_color(1.0, 0.0, 0.0)
#define GREEN new_color(0.0, 1.0, 0.0)
#define BLUE  new_color(0.0, 0.0, 1.0)
#define WHITE new_color(1.0, 1.0, 1.0)

/* A struct representing a color. */
typedef struct color
{
    double red;
    double green;
    double blue;
} color;

/* A struct representing colors from 0-255. */
typedef struct color_int
{
    int red;
    int green;
    int blue;
} color_int;

/* Create a new color given the RGB values. */
color new_color(double red, double green, double blue);

/* Add two colors. */
color color_add(color* c1, color* c2);
/* Subtract two colors */
color color_sub(color* c1, color* c2);
/* Multiply two colors by scalar */
color color_mul(double c, color* c2);
/* Calculate the hadamard product of colors */
color color_hadamard(color* c1, color* c2);

/* Convert a color_double to color_int */
color_int color_to_int(color* c);

/* Approximated equality between two colors. */
int c_approx(color* c1, color* c2);
#endif 