#include "cub3d.h"

// Because the cos and sin functions need a radian value,
// not degrees
double	convert_degrees_to_rad(float degree)
{
	double radian;

	radian = degree *  M_PI / 180;
	return (radian);
}

double	calculate_distance(double deltaX, double deltaY)
{
	double	distance;

	distance = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	return (distance);
}

void	draw_line(void *mlx, void *window, int beginX, int beginY, int endX, int endY, int color)
{
	double deltaX = endX - beginX;
	double deltaY = endY - beginY;

	int pixels = calculate_distance(deltaX, deltaY);

	deltaX /= pixels;
	deltaY /= pixels;

	double pixelX = beginX;
	double pixelY = beginY;
	while (pixels)
	{
		mlx_pixel_put(mlx, window, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}

}