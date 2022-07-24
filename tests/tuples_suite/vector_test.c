#include "../bdd_tap.h"

#include <raytracer/tuple.h>
#include <raytracer/raytracer_utils.h>

spec("A tuple with w=0.0 (4.3, -4.2, 3.1, 0.0)")
{
    tuple a  = t_new(4.3, -4.2, 3.1, 0.0);

    it ("a.x = 4.3")
    {
        check(approx_d(a.x, 4.3));
    }

    it ("a.y = -4.2")
    {
        check(approx_d(a.y, -4.2));
    }

    it ("a.z = 3.1") 
    {
        check(approx_d(a.z, 3.1));
    }
    
    it ("is a vector.")
    {
        check(approx_d(a.w, 0.0));
    }

}