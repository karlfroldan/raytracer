#include "matrix.h"

/* Instantiate a new matrix.
The input is a list of values in row-major order.
If the list is shorter than 16 values, then the 
others will be filled with 0s. */
// matrix m_new(double* vals, int n) 
// {
//     tuple rs[4];

//     int p = 0;

//     for (int i = 0; i < 4; ++i) 
//         rs[i] = ZERO_T;

//     for (int i = 0; i < n; ++i)
//     {
//         /* Which tuple? */
//         int k = i / 4;
//         /* Which index? */
//         int j = i % 4;

//         if (j == 0)
//             rs[k].x = vals[i];
//         else if (j == 1)
//             rs[k].y = vals[i];
//         else if (j == 2)
//             rs[k].z = vals[i];
//         else
//             rs[k].w = vals[i];
//         p++;
//     }

//     for (; p < 16; ++p)
//     {
//         /* Which tuple? */
//         int k = p / 4;
//         /* Which index? */
//         int j = p % 4;

//         if (j == 0)
//             rs[k].x = 0;
//         else if (j == 1)
//             rs[k].y = 0;
//         else if (j == 2)
//             rs[k].z = 0;
//         else
//             rs[k].w = 0;
//         p++;
//     }

//     matrix m = {rs[0], rs[1], rs[2], rs[3]};
//     return m;
// }