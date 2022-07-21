#ifndef RAYTRACER_MATRIX_TRANSFORMATIONS_H
#define RAYTRACER_MATRIX_TRANSFORMATIONS_H

#include "matrix.h"
#include "tuple.h"

#define XAXIS 0
#define YAXIS 1
#define ZAXIS 2

#define PI 3.14159265359

/* Create a translation matrix */
matrix translate(double x, double y, double z);

/* Create a scaling matrix. */
matrix scale(double x, double y, double z);

/* Rotate along an axis. */
matrix rotate(int axis, double theta);

/* Shearing transformation */
matrix shear(double x_y, double x_z, double y_x, double y_z, double z_x, double z_y);

/* Apply matrix transformation. Unlike simple multiplication, this copies the matrix and tuple
and is therefore not efficient. */
tuple apply(matrix, tuple);

/* Chain matrix transformations. Unlike matrix multiplication, this is not efficient since
it copies the matrix and tuple. */
matrix chain(matrix, matrix);

#endif