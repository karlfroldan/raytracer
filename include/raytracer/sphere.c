#include "sphere.h"
#include <time.h>
#include <stdlib.h>

#include "matrix.h"

sphere new_sphere()
{
    sphere s = { m_id(4) };

    return s;
}
