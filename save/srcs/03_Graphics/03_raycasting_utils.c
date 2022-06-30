#include "cub3d.h"

/**
 * @brief Converts the rgb values into a hexadecimal one, in order to be used
 * 		  in the my_mlx_pixel_put function.
 * 
 */
int	rgb_to_hex(int red, int green, int blue)
{
	int	color;

	color = ((int)(red & 0xff) << 16) + ((int)(green & 0xff) << 8)
		+ (int)(blue & 0xff);
	return (color);
}

/**
 * @brief Prints a pixel on the window
 * 
 */
void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char    *pixel;

    pixel = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)pixel = color;
}

/**
 * @brief Prints either the ceiling/sky or the floor of a map
 * 
 */
void	display_background(unsigned long color, t_img *img, int start, int end, int x)
{
	if (start < 0)
		start = 0;
	while (start < end)
	{
		my_mlx_pixel_put(img, x, start, color);
		start++;
	}
}
