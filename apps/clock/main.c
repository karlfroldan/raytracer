#include <stdio.h>

#include <raytracer/matrix.h>
#include <raytracer/matrix_transformations.h>
#include <raytracer/canvas.h>

#include <math.h>

const double HOUR_ROTATION = PI/6;

int trim(double x)
{
    return (int) round(x);
}

int main()
{
    canvas c = new_canvas(200, 200);
    matrix rotation = rotate(YAXIS, HOUR_ROTATION);
    matrix scaling = scale(80, 80, 80);
    matrix translated = translate(100, 0, 100);

    tuple clock_pos = point(0, 0, 1);
    tuple scaled, moved;

    int x_pos, y_pos;

    for (int i = 0; i < 12; ++i) 
    {
        scaled = m_mul_tuple(&scaling, &clock_pos);
        moved = m_mul_tuple(&translated, &scaled);

        x_pos = trim(moved.x);
        y_pos = trim(moved.z);

        write_color(&c, WHITE, x_pos, y_pos);

        // print neighbors.
        write_color(&c, WHITE, x_pos - 1, y_pos);
        write_color(&c, WHITE, x_pos + 1, y_pos);
        write_color(&c, WHITE, x_pos, y_pos - 1);
        write_color(&c, WHITE, x_pos, y_pos + 1);

        clock_pos = m_mul_tuple(&rotation, &clock_pos);
    }

    char* _ppm = ppm(&c);

    FILE* ppm_file = fopen("clock.ppm", "w");

    fprintf(ppm_file, "%s", _ppm);

    fclose(ppm_file);

    return 0;
}