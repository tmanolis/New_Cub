#include "cub3d.h"

/**
 * @brief Set the wall textures according to the direction filled (N, S, W, E)
 * 
 */
static char	*set_wall_direction(t_data *data, t_raycast *ray)
{
	if (ray->side == NO)
		return (data->tex.no.addr);
	else if (ray->side == SO)
		return (data->tex.so.addr);
	else if (ray->side == EA)
		return (data->tex.ea.addr);
	else
		return (data->tex.we.addr);
}

/**
 * @brief Get the right color for r, g or b values according to their index
 * 			in the array tex_addr.
 * 
 */
static int	get_rgb(char *tex_addr, t_raycast *ray, t_data *data, int add, int y)
{
	int	rgb;

	rgb = tex_addr[(int)(ray->wallX * T_WIDTH) * (data->tex.no.bits_per_pixel >> 3)
			+ add + (int)((y - ray->drawStart * 1.0) 
				/ ray->lineHeight * T_HEIGHT) * data->tex.no.line_length];
	return (rgb);
}

/**
 * @brief Get the right colors and display the wall textures according to their
 * 			cardinal direction.
 * 
 */
static void	display_wall_textures(t_data *data, t_raycast *ray, t_img *img, int x)
{
	int		color;
	int		r;
	int		g;
	int		b;
	char	*tex_addr;

	tex_addr = set_wall_direction(data, ray);
	for (int y = ray->drawStart; y < ray->drawEnd; y++)
	{
		r = get_rgb(tex_addr, ray, data, 2, y);
		g = get_rgb(tex_addr, ray, data, 1, y);
		b = get_rgb(tex_addr, ray, data, 0, y);
		color = rgb_to_hex(r, g, b);
		if (ray->side == SO || ray->side ==  NO)
			color = (color >> 1) & 8355711;
		my_mlx_pixel_put(img, x, y, color);
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
	unsigned long	ceiling;
	unsigned long	floor;
	int				x;

	map = &data->map;
	ray = &data->ray;
	ceiling = data->graphics.hex_ceiling;
	floor = data->graphics.hex_floor;
	x = 0;
	while (x < data->win_width)
	{
		init_raycasting_variables(data, ray, map, x);
		calculate_raydirx_and_stepx(ray, map);
		which_distance_if_wall_hit(ray);
		calculate_wall_specs(data, ray, map);
		display_background(ceiling, img, 0, ray->drawStart, x);
		display_wall_textures(data, ray, img, x);
		display_background(floor, img, ray->drawEnd, W_HEIGHT, x);
		x++;
	}
}