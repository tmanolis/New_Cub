/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_raycasting_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmanolis <tmanolis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 18:46:44 by tmanolis          #+#    #+#             */
/*   Updated: 2022/06/30 19:59:07 by tmanolis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	char	*pixel;

	pixel = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)pixel = color;
}

void	display_ceiling(t_data *data, t_img *img, int start, int end)
{
	if (start < 0)
		start = 0;
	while (start < end)
	{
		my_mlx_pixel_put(img, data->pixel, start, data->graphics.hex_ceiling);
		start++;
	}
}

void	display_floor(t_data *data, t_img *img, int start, int end)
{
	if (start < 0)
		start = 0;
	while (start < end)
	{
		my_mlx_pixel_put(img, data->pixel, start, data->graphics.hex_floor);
		start++;
	}
}
