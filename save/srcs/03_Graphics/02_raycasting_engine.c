/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_raycasting_engine.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 18:42:44 by tmanolis          #+#    #+#             */
/*   Updated: 2022/06/30 20:18:33 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Set the wall textures according to the direction filled (N, S, W, E)
 * 
 */
static char	*set_wall_direction(t_data *data, t_raycast *ray)
{
	if (ray->side == NO)
		return (data->tex.we.addr);
	else if (ray->side == SO)
		return (data->tex.ea.addr);
	else if (ray->side == EA)
		return (data->tex.so.addr);
	else
		return (data->tex.no.addr);
}

/**
 * @brief Get the right color for r, g or b values according to their index
 * 			in the array tex_addr.
 * 
 */
static int	get_rgb(char *tex_addr, t_data *data, int add, int y)
{
	int	rgb;

	rgb = tex_addr[(int)(data->ray.wall_x * T_WIDTH)
		* (data->tex.no.bits_per_pixel >> 3)
		+ add + (int)((y - data->ray.draw_start * 1.0)
			/ data->ray.line_height * T_HEIGHT)*data->tex.no.line_length];
	return (rgb);
}

/**
 * @brief Get the right colors and display the wall textures according to their
 * 			cardinal direction.
 * 
 */
static void	display_wall_tex(t_data *data, t_raycast *ray, t_img *img, int x)
{
	int		color;
	int		rgb[3];
	char	*tex_addr;
	int		y;

	tex_addr = set_wall_direction(data, ray);
	if (ray->draw_start < 0)
		y = 0 ;
	else
		y = ray->draw_start;
	while (y < ray->draw_end)
	{
		rgb[0] = get_rgb(tex_addr, data, 2, y);
		rgb[1] = get_rgb(tex_addr, data, 1, y);
		rgb[2] = get_rgb(tex_addr, data, 0, y);
		color = rgb_to_hex(rgb[0], rgb[1], rgb[2]);
		if (ray->side == EA || ray->side == WE)
			color = (color >> 1) & 8355711;
		my_mlx_pixel_put(img, x, y, color);
		y++;
	}
}

/**
 * @brief The main function doing the raycasting. Everything is done inside the
 * 			while loop. Loosely, there are 3 steps:
 * 				1) init the variables (the rays)
 * 				2) calculate the hit between a ray and a wall, as well as its
 * 					distance
 * 				3) display the walls, as well as the sky/ceiling and the floor
 * 
 */
void	calculate_and_display(t_data *data, t_img *img)
{
	t_map			*map;
	t_raycast		*ray;

	map = &data->map;
	ray = &data->ray;
	data->pixel = 0;
	while (data->pixel < data->win_width)
	{
		init_raycasting_var(data, ray, map, data->pixel);
		calculate_raydir_x_and_step_x(ray, map);
		which_distance_if_wall_hit(ray, map);
		calculate_wall_specs(data, ray, map);
		display_ceiling(data, img, 0, ray->draw_start);
		display_wall_tex(data, ray, img, data->pixel);
		display_floor(data, img, ray->draw_end, W_HEIGHT);
		data->pixel++;
	}
}
