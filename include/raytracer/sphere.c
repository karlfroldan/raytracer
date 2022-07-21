#include "sphere.h"
#include <time.h>
#include <stdlib.h>

sphere new_sphere()
{
    sphere s = { rand() };

    return s;
}
