#include "../bdd-for-c.h"

#include <raytracer/tuple.h>
#include <raytracer/raytracer_utils.h>

spec("A tuple with w=1.0 (4.3, -4.2, 3.1, 1.0)")
{
    tuple a = new_tuple4(4.3, -4.2, 3.1, 1.0);

    it ("a.x = 4.3")
    {
        check(approx_d(_x(&a), 4.3));
    }

    it ("a.y = -4.2")
    {
        check(approx_d(_y(&a), -4.2));
    }

    it ("a.z = 3.1") 
    {
        check(approx_d(_z(&a), 3.1));
    }
    
    it ("is a point.")
    {
        check(approx_d(_w(&a), 1.0));
    }

    t_free(&a);
}