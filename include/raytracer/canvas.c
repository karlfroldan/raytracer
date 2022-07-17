#include "canvas.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Create a new canvas initialized to BLACK. */
canvas new_canvas(int width, int height)
{
    canvas c = {
        malloc(sizeof(color) * width * height),
        width, height
    };

    for (int i = 0; i < width * height; ++i)
        c.c_data[i] = BLACK;

    return c;
}

/* Get a pointer to the current color in the canvas point */
color* 
pixel_at(canvas* c, int x, int y)
{
    /* if the element we're accessing is outside the canvas, 
    then return null. */
    if (y >= c->height || x >= c->width)
        return NULL;

    /* Return the address of the color on this offset. */
    return  &(c->c_data[y * c->width + x]);
    
}

/* Verify if the given canvas point is black. */
int is_black(canvas* c, int x, int y)
{
    color* pixel = pixel_at(c, x, y);
    color black = BLACK;
    return c_approx(pixel, &black);
}

/* Free the canvas */
void c_free(canvas* c)
{
    free(c->c_data);
    c->height = 0;
    c->width = 0;
}

/* Write a given color to the canvas */
void 
write_color(canvas* c, color _color, int x, int y)
{
    if (y >= c->height || x >= c->width)
        return;

    color* t = pixel_at(c, x, y);
    t->red   = _color.red;
    t->green = _color.green;
    t->blue   = _color.blue;
}

/* write color at the buffer, given the value. Returns the next character count. 
This is a bad comment 'cause I'm writing this late at night. */
int write_color_at(char** buffer, int val, int char_counter)
{
    int allocated_size = 0;
    /* Write RED to our buffer. */
    sprintf(*buffer, "%d", val);

    /* How many characters were written? */
    allocated_size = strlen(*buffer);
    char_counter += allocated_size;
    /* Move our buffer pointer. */
    *buffer += allocated_size;


    /* If we're nearing 70 characters, append a newline. */
    if (char_counter >= 66)
    {
        sprintf(*buffer, "\n");
        char_counter = 0;
    }
    else
    {
        sprintf(*buffer, " ");
        char_counter++;
    }
    (*buffer)++;
    return char_counter;
}

/* This function is for testing purposes only. */
char* ppm(canvas* c)
{
    int buffer_size = 30 + (c->height * c->width * 4);
    char* buffer = NULL;

    if ((buffer = malloc(sizeof(char) * buffer_size)) == NULL)
    {
        fprintf(stderr, "Cannot generate PPM.\nOut of memory.\n");
        return NULL;
    }

    /* The buf_pntr will point to the current place on where we will write our string. */
    char* buf_pntr = buffer;

    /* Header buffer for the PPM header. */
    char header[50];

    sprintf(header, "P3\n%d %d\n255\n", c->width, c->height);
    int header_size = strlen(header);

    strncpy(buffer, header, header_size);

    /**
     * We will start drawing from this point. Right now, our buf_pntr
     * is pointing to the next character after the new line.
     */
    buf_pntr = buf_pntr + header_size;

    /* The char_counter counts how many characters are currently in the PPM row. */
    int char_counter = 0;

    for (int j = 0; j < c->height; ++j)
    {
        for (int i = 0; i < c->width; ++i)
        {
            color* c1 = pixel_at(c, i, j);
            color_int c2 = color_to_int(c1);

            char_counter = write_color_at(&buf_pntr, c2.red, char_counter);
            char_counter = write_color_at(&buf_pntr, c2.green, char_counter);
            char_counter = write_color_at(&buf_pntr, c2.blue, char_counter);
        }

        /* If we did not just reach a new line. */
        if (*(buf_pntr - 1) != '\n')
        {
            sprintf(buf_pntr, "\n");
            buf_pntr++;
        }

        char_counter = 0;
        
    }

    sprintf(buf_pntr, "\n");

    return buffer;
}