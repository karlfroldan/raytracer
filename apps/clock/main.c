#include <stdio.h>

#include <raytracer/matrix.h>
#include <raytracer/matrix_transformations.h>
#include <raytracer/canvas.h>

#include <math.h>

const int CANVAS_SIZE = 500;
const int SCALE_FACTOR = (int) CANVAS_SIZE * 0.40;
const int TRANSLATE_FACTOR = CANVAS_SIZE / 2;
const double HOUR_ROTATION = PI/6;

int trim(double x)
{
    return (int) round(x);
}

int main()
{
    canvas c = new_canvas(CANVAS_SIZE, CANVAS_SIZE);
    matrix rotation = rotate(YAXIS, HOUR_ROTATION);
    matrix scaling = scale(SCALE_FACTOR, SCALE_FACTOR, SCALE_FACTOR);
    matrix translated = translate(TRANSLATE_FACTOR, 0, TRANSLATE_FACTOR);

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