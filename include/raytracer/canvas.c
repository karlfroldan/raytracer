#include "canvas.h"

#include <stdlib.h>

#include <stdio.h>

#define BLACK new_tuple4(0.0, 0.0, 0.0, 0.0);

/* Create a new canvas initialized to BLACK. */
canvas new_canvas(int height, int width)
{
    canvas c = {
        malloc(sizeof(tuple) * width * height),
        height, width
    };

    for (int i = 0; i < width * height; ++i)
        c.c_data[i] = BLACK;

    return c;
}

/* Get a pointer to the current color in the canvas point */
tuple* 
pixel_at(canvas* c, int row, int col)
{
    /* if the element we're accessing is outside the canvas, 
    then return null. */
    if (row >= c->height || col >= c->width)
        return NULL;

    /* Return the address of the color on this offset. */
    printf("Offset: %d * %d + %d = %d\n", row, c->width, col, row * c->width + col);
    fflush(stdout);
    return  &(c->c_data[row * c->width + col]);
    
}

/* Verify if the given canvas point is black. */
int is_black(canvas* c, int row, int col)
{
    tuple* pixel = pixel_at(c, row, col);
    tuple black = BLACK;
    return t_approx(pixel, &black);
}

/* Free the canvas */
void c_free(canvas* c)
{
    free(&(c->c_data));
    c->height = 0;
    c->width = 0;
}

/* Write a given color to the canvas */
void 
write_color_1(canvas* c, double red, double green, double blue, int row, int col)
{
    if (row >= c->height || col >= c->width)
        return;

    tuple* t = pixel_at(c, row, col);
    t->arr[0] = red;
    t->arr[1] = green;
    t->arr[2] = blue;
}