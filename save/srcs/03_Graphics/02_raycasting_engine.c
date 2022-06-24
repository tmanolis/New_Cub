#include "cub3d.h"

int	rgb_to_hex(int r, int g, int b)
{
	int	color;

	color = ((int)(r & 0xff) << 16) + ((int)(g & 0xff) << 8)
		+ (int)(b & 0xff);
	return (color);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char    *pixel;

    pixel = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)pixel = color;
}

void	init_img_to_display(t_data *data, t_img *bite)
{
	bite->mlx_img = mlx_new_image(data->mlx, data->win_width, data->win_height);
	bite->addr = mlx_get_data_addr(bite->mlx_img, &data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
	bite->line_length = data->img.line_length;
	bite->endian= data->img.endian;
	bite->bits_per_pixel= data->img.bits_per_pixel;
}

void	init_raycasting_variables(t_data *data, t_raycast *ray, t_map *map, int x)
{
	ray->cameraX = 2 * x / (double)data->win_width - 1;
	ray->rayDirX = map->dir_x + map->plane_x * ray->cameraX;
	ray->rayDirY = map->dir_y + map->plane_y * ray->cameraX;
	ray->mapX = (int)map->pos_x;
	ray->mapY = (int)map->pos_y;
	ray->deltaDistX = fabs(1 / ray->rayDirX);
	ray->deltaDistY = fabs(1 / ray->rayDirY);
	ray->hit = 0; 
}

void	calculate_raydirx_and_stepx(t_raycast *ray, t_map *map)
{
	if (ray->rayDirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (map->pos_x - ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - map->pos_x) * ray->deltaDistX;
	}
	if (ray->rayDirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (map->pos_y - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - map->pos_y) * ray->deltaDistY;
	}
}

void	which_distance_if_wall_hit(t_raycast *ray)
{
	while (ray->hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			ray->side = (ray->rayDirX > 0) ? EA : WE;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = (ray->rayDirY > 0) ? SO : NO;
		}
		if (worldMap[ray->mapX][ray->mapY] == 1) 
			ray->hit = 1;
	}
}

void	calculate_wall_specs(t_data *data, t_raycast *ray, t_map *map)
{
	if (ray->side == EA || ray->side == WE)
		ray->perpWallDist = (ray->mapX - map->pos_x + (1 - ray->stepX) / 2) / ray->rayDirX;
	else
		ray->perpWallDist = (ray->mapY - map->pos_y + (1 - ray->stepY) / 2) / ray->rayDirY;
	ray->lineHeight = (int)(data->win_height / ray->perpWallDist);
	ray->drawStart = -(ray->lineHeight) / 2 + data->win_height / 2;
	if(ray->drawStart < 0)
		ray->drawStart = 0;
	ray->drawEnd = ray->lineHeight / 2 + data->win_height / 2;
	if(ray->drawEnd >= data->win_height)
		ray->drawEnd = data->win_height - 1;
	if (ray->side == EA || ray->side == WE)
		ray->wallX = map->pos_y + ray->perpWallDist * ray->rayDirY;
	else
		ray->wallX = map->pos_x + ray->perpWallDist * ray->rayDirX;
	ray->wallX -= floor(ray->wallX);
}

void	display_background(unsigned long color, t_img *img, int start, int end, int x)
{
	while (start < end)
	{
		my_mlx_pixel_put(img, x, start, color);
		start++;
	}
}

/**
 * @brief Set the wall textures according to the direction filled (N, S, W, E)
 * 
 */
char	*set_wall_direction(t_data *data, t_raycast *ray)
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

int	get_rgb(char *tex_addr, t_raycast *ray, t_data *data, int add, int y)
{
	int	rgb;

	rgb = tex_addr[(int)(ray->wallX * T_WIDTH) * (data->tex.no.bits_per_pixel >> 3)
			+ add + (int)((y - ray->drawStart * 1.0) 
				/ ray->lineHeight * T_HEIGHT) * data->tex.no.line_length];
	return (rgb);
}

void	display_wall_textures(t_data *data, t_raycast *ray, t_img *img, int x)
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

void	calculate_and_display(t_data *data, t_img *bite)
{
	t_map		*map;
	t_raycast	*ray;
	int			x;

	map = &data->map;
	ray = &data->ray;
	x = 0;
	while (x < data->win_width)
	{
		init_raycasting_variables(data, ray, map, x);
		calculate_raydirx_and_stepx(ray, map);
		which_distance_if_wall_hit(ray);
		calculate_wall_specs(data, ray, map);
		display_background(data->graphics.hex_ceiling, bite, 0, ray->drawStart, x);
		display_wall_textures(data, ray, bite, x);
		display_background(data->graphics.hex_floor, bite, ray->drawEnd, W_HEIGHT, x);
		x++;
	}
}

int	raycasting_loop(t_data *data)
{
	t_img		tmp_img;

	init_img_to_display(data, &tmp_img);
	calculate_and_display(data, &tmp_img);
	mlx_put_image_to_window(data->mlx, data->win, tmp_img.mlx_img, 0, 0);
	if (data->img.mlx_img)
		mlx_destroy_image(data->mlx, data->img.mlx_img);
	data->img.mlx_img = tmp_img.mlx_img;
	data->img.addr =  tmp_img.addr;
	return (0);
}