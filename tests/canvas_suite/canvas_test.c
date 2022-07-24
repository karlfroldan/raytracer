#include <raytracer/canvas.h>

#include "../bdd_tap.h"
#include <string.h>
#include <raytracer/color.h>

spec("Canvas Tests")
{
    it("Creating a canvas")
    {
        canvas c = new_canvas(10, 20);

        check(c.width == 10);
        check(c.height == 20);

        int all_black = 1;
        
        for (int i = 0; i < 10; ++i)
        {
            for (int j = 0; j < 20; ++j)
                all_black = all_black && is_black(&c, i, j);
        }

        check(all_black);

        c_free(&c);
    }

    it("Writing pixels to a canvas")
    {
        canvas c = new_canvas(10, 20);

        color red = RED;
        color expectation = RED;

        write_color(&c, red, 2, 3);
        color* p = pixel_at(&c, 2, 3);

        check(c_approx(p, &expectation));

        c_free(&c);
    }

    it("Constructing the PPM File")
    {
        canvas c = new_canvas(5, 3);

        color c1 = new_color(1.5, 0, 0);
        color c2 = new_color(0, 0.5, 0);
        color c3 = new_color(-0.5, 0, 1);

        write_color(&c, c1, 0, 0);
        write_color(&c, c2, 2, 1);
        write_color(&c, c3, 4, 2);

        char* image = ppm(&c);
        char* expected = "P3\n 5 3\n255\n255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n";

        check(strncmp(image, expected, 107));
    }
}