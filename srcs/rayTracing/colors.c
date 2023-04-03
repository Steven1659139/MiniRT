#include "../../include/miniRT.h"
#include <math.h>


t_rgba separate_color_rgba(int32_t color)
{
	t_rgba rgba;

	rgba.r = (color >> 24) & 0xFF;
	rgba.g = (color >> 16) & 0xFF;
	rgba.b = (color >> 8) & 0xFF;
	rgba.a = color & 0xFF;
	return (rgba);
}

int32_t mix_colors(int32_t colorA, int32_t colorB, double ratio)
{
	t_rgba	N;
	t_rgba	A = separate_color_rgba(colorA);
	t_rgba	B = separate_color_rgba(colorB);

	(void)ratio;
    // N.r = (int)((1.0 - ratio) * A.r + ratio * B.r);
    // N.g = (int)((1.0 - ratio) * A.g + ratio * B.g);
    // N.b = (int)((1.0 - ratio) * A.b + ratio * B.b);

	N.r = (A.r + B.r) / 2;
	N.g = (A.g + B.g) / 2;
	N.b = (A.b + B.b) / 2;

    return ((N.r << 24) | (N.g << 16) | (N.b << 8) | N.a);
}

int32_t brightness(int32_t color, double scale) 
{
	t_rgba rgba = separate_color_rgba(color);

	rgba.r *= scale;
	rgba.g *= scale;
	rgba.b *= scale;

	return ((rgba.r << 24) | (rgba.g << 16) | (rgba.b << 8) | rgba.a);
}

double remap(double a, double b, double t)
{
	return ((t-a)/(b-a));
}
