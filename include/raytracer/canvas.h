#ifndef RAYTRACER_CANVAS_H
#define RAYTRACER_CANVAS_H

#include "color.h"



typedef struct canvas
{
    /* An array of tuples. Canvas is 2D but we can access 
    the elements using an offset anyways. 

    Our canvas memory is laid out as
    ROW0 col2 col3 col4... ROW1 col2 col3 col4...
    y    y+1  y+2  y+3     (y*width) (y*width)+1

    So to get the current c_data, 
    c[x][y] = c[y * width + x]
    */
    color* c_data; 
    int width;  /* These two are */
    int height;   /* pretty self-explanatory */
} canvas;

/* Create a new canvas initialized to BLACK. */
canvas new_canvas(int width, int height);

/* Get a pointer to the current color in the canvas point */
color* pixel_at(canvas*, int row, int col);

/* Write a given color to the canvas */
void write_color(canvas*, color _color, int x, int y);

/* Write a given color to a canvas given some color */


/* Verify if the given canvas point is black. */
int is_black(canvas*, int row, int col);

/* Free the canvas */
void c_free(canvas*);

char* ppm(canvas*);

#endif /* RAYTRACER_CANVAS_H */