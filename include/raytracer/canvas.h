#ifndef RAYTRACER_CANVAS_H
#define RAYTRACER_CANVAS_H

#include "tuple.h"



typedef struct canvas
{
    /* An array of tuples. Canvas is 2D but we can access 
    the elements using an offset anyways. 

    Our canvas memory is laid out as
    ROW1 col2 col3 col4... ROW2 col2 col3 col4...

    So to get the current c_data, 
    c[row][col] = c[row * width + col]
    */
    tuple* c_data; 
    int height;  /* These two are */
    int width;   /* pretty self-explanatory */
} canvas;

/* Create a new canvas initialized to BLACK. */
canvas new_canvas(int width, int height);

/* Get a pointer to the current color in the canvas point */
tuple* pixel_at(canvas*, int row, int col);

/* Write a given color to the canvas */
void write_color_1(canvas*, double red, double green, double blue, int row, int col);

/* Write a given color to a canvas given some color */


/* Verify if the given canvas point is black. */
int is_black(canvas*, int row, int col);

/* Free the canvas */
void c_free(canvas*);

#endif /* RAYTRACER_CANVAS_H */