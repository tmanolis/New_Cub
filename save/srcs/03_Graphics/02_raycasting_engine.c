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

	// //length of ray from current position to next x or y-side
	// double sideDistX;
	// double sideDistY;
	
	//length of ray from one x or y-side to next x or y-side
	ray->deltaDistX = fabs(1 / ray->rayDirX);
	ray->deltaDistY = fabs(1 / ray->rayDirY);
	// double perpWallDist;
	
	//what direction to step in x or y-direction (either +1 or -1)
	// int stepX;
	// int stepY;
	
	ray->hit = 0; //was there a wall hit?
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
		//jump to next map square, OR in x-direction, OR in y-direction
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			// ray->side = 0;
			ray->side = (ray->rayDirX > 0) ? EA : WE;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			// ray->side = 1;
			ray->side = (ray->rayDirY > 0) ? SO : NO;
		}
		//Check if ray has hit a wall
		
		if (worldMap[ray->mapX][ray->mapY] == 1) 
			ray->hit = 1;
	}
}

void	calculate_wall_specs(t_data *data, t_raycast *ray, t_map *map)
{
	if (ray->side == EA || ray->side == WE)  // ray->side == 0
		ray->perpWallDist = (ray->mapX - map->pos_x + (1 - ray->stepX) / 2) / ray->rayDirX;
	else
		ray->perpWallDist = (ray->mapY - map->pos_y + (1 - ray->stepY) / 2) / ray->rayDirY;

	//Calculate height of line to draw on screen
	ray->lineHeight = (int)(data->win_height / ray->perpWallDist);

	//calculate lowest and highest pixel to fill in current stripe
	ray->drawStart = -(ray->lineHeight) / 2 + data->win_height / 2;
	if(ray->drawStart < 0)
		ray->drawStart = 0;
	ray->drawEnd = ray->lineHeight / 2 + data->win_height / 2;
	if(ray->drawEnd >= data->win_height)
		ray->drawEnd = data->win_height - 1;

	// double wallX;
	if (ray->side == EA || ray->side == WE) // ray->side == 0
		ray->wallX = map->pos_y + ray->perpWallDist * ray->rayDirY;
	else
		ray->wallX = map->pos_x + ray->perpWallDist * ray->rayDirX;
	ray->wallX -= floor(ray->wallX);
}

void	display_background(unsigned long color, t_img *img, int start, int end, int x)
{
	// CEILING
	// int y = 0;
	// while (y < ray->drawStart)
	// {
	// // my_mlx_pixel_put(&bite, x, y, 0xFFFF00);
		// my_mlx_pixel_put(&bite, x, y, data->graphics.hex_ceiling);
	// 	y++;
	// }

	// FLOOR
	// y = ray->drawEnd;
	// while (y < W_HEIGHT) {
	// my_mlx_pixel_put(&bite, x, y, data->graphics.hex_floor);
	// y++;

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
// char	*set_wall_direction()
// {
// 	if 
// }

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
	
	for (int y = ray->drawStart; y < ray->drawEnd; y++)
	{
		// r = data->tex.no.addr[(int)(ray->wallX * T_WIDTH) * (data->tex.no.bits_per_pixel >> 3)
		// 	+ 2 + (int)((y - ray->drawStart * 1.0) 
		// 		/ ray->lineHeight * T_HEIGHT) * data->tex.no.line_length];
		// g = data->tex.no.addr[(int)(ray->wallX * T_WIDTH) * (data->tex.no.bits_per_pixel >> 3)
		// 	+ 1 + (int)((y - ray->drawStart * 1.0)
		// 		/ ray->lineHeight * T_HEIGHT) *data->tex.no.line_length];
		// b = data->tex.no.addr[(int)(ray->wallX * T_WIDTH) * (data->tex.no.bits_per_pixel >> 3)
		// 	+ 0 + (int)((y - ray->drawStart * 1.0)
		// 		/ ray->lineHeight * T_HEIGHT) *data->tex.no.line_length];

		// tex_addr = set_wall_direction();
		r = get_rgb(data->tex.no.addr, ray, data, 2, y);
		g = get_rgb(data->tex.no.addr, ray, data, 1, y);
		b = get_rgb(data->tex.no.addr, ray, data, 0, y);
		// r = get_rgb(tex_addr, ray, data, 2, y);
		// g = get_rgb(tex_addr, ray, data, 1, y);
		// b = get_rgb(tex_addr, ray, data, 0, y);
		color = rgb_to_hex(r, g, b);
		// make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		if (ray->side == SO || ray->side ==  NO)
			color = (color >> 1) & 8355711;
		my_mlx_pixel_put(img, x, y, color);
	}
}

void	calc(t_data *data)
{
	t_map		*map;
	t_raycast	*ray;
	t_img		bite;
	int			x;

	map = &data->map;
	ray = &data->ray;
	x = 0;

	init_img_to_display(data, &bite); // 12:05 - COMPILED AND RUN : OK
	// bite.mlx_img = mlx_new_image(data->mlx, data->win_width, data->win_height);
	// bite.addr = mlx_get_data_addr(bite.mlx_img, &data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
	// bite.line_length = data->img.line_length;
	// bite.endian= data->img.endian;
	// bite.bits_per_pixel= data->img.bits_per_pixel;

	while (x < data->win_width)
	{
		init_raycasting_variables(data, ray, map, x); // 12:08 - COMPILED AND RUN : OK
		// ray->cameraX = 2 * x / (double)data->win_width - 1;
		// ray->rayDirX = map->dir_x + map->plane_x * ray->cameraX;
		// ray->rayDirY = map->dir_y + map->plane_y * ray->cameraX;
		
		// ray->mapX = (int)map->pos_x;
		// ray->mapY = (int)map->pos_y;

		// // //length of ray from current position to next x or y-side
		// // double sideDistX;
		// // double sideDistY;
		
		//  //length of ray from one x or y-side to next x or y-side
		// ray->deltaDistX = fabs(1 / ray->rayDirX);
		// ray->deltaDistY = fabs(1 / ray->rayDirY);
		// // double perpWallDist;
		
		// //what direction to step in x or y-direction (either +1 or -1)
		// // int stepX;
		// // int stepY;
		
		// ray->hit = 0; //was there a wall hit?
		// int side; //was a NS or a EW wall hit?

		calculate_raydirx_and_stepx(ray, map); // 12:12 - COMPILED AND RUN : OK
		// if (ray->rayDirX < 0)
		// {
		// 	ray->stepX = -1;
		// 	ray->sideDistX = (map->pos_x - ray->mapX) * ray->deltaDistX;
		// }
		// else
		// {
		// 	ray->stepX = 1;
		// 	ray->sideDistX = (ray->mapX + 1.0 - map->pos_x) * ray->deltaDistX;
		// }
		// if (ray->rayDirY < 0)
		// {
		// 	ray->stepY = -1;
		// 	ray->sideDistY = (map->pos_y - ray->mapY) * ray->deltaDistY;
		// }
		// else
		// {
		// 	ray->stepY = 1;
		// 	ray->sideDistY = (ray->mapY + 1.0 - map->pos_y) * ray->deltaDistY;
		// }


		which_distance_if_wall_hit(ray); // 13:19 - COMPILED AND RUN : OK
		// while (ray->hit == 0)
		// {
		// 	//jump to next map square, OR in x-direction, OR in y-direction
		// 	if (ray->sideDistX < ray->sideDistY)
		// 	{
		// 		ray->sideDistX += ray->deltaDistX;
		// 		ray->mapX += ray->stepX;
		// 		ray->side = 0;
		// 	}
		// 	else
		// 	{
		// 		ray->sideDistY += ray->deltaDistY;
		// 		ray->mapY += ray->stepY;
		// 		ray->side = 1;
		// 	}
		// 	//Check if ray has hit a wall
			
		// 	if (worldMap[ray->mapX][ray->mapY] == 1) 
		// 		ray->hit = 1;
		// }

		calculate_wall_specs(data, ray, map); // 13:23 - COMPILED AND RUN : OK
		// if (ray->side == 0)
		// 	ray->perpWallDist = (ray->mapX - map->pos_x + (1 - ray->stepX) / 2) / ray->rayDirX;
		// else
		// 	ray->perpWallDist = (ray->mapY - map->pos_y + (1 - ray->stepY) / 2) / ray->rayDirY;

		// //Calculate height of line to draw on screen
		// ray->lineHeight = (int)(data->win_height / ray->perpWallDist);

		// //calculate lowest and highest pixel to fill in current stripe
		// ray->drawStart = -(ray->lineHeight) / 2 + data->win_height / 2;
		// if(ray->drawStart < 0)
		// 	ray->drawStart = 0;
		// ray->drawEnd = ray->lineHeight / 2 + data->win_height / 2;
		// if(ray->drawEnd >= data->win_height)
		// 	ray->drawEnd = data->win_height - 1;

		// double wallX;
		// if (ray->side == 0)
		// 	wallX = map->pos_y + ray->perpWallDist * ray->rayDirY;
		// else
		// 	wallX = map->pos_x + ray->perpWallDist * ray->rayDirX;
		// wallX -= floor(wallX);


		// x coordinate on the texture
		// int texX = (int)(ray->wallX * (double)T_WIDTH);
		// if (ray->side == 0 && ray->rayDirX > 0)
		// 	texX = T_WIDTH - texX - 1;
		// if (ray->side == 1 && ray->rayDirY < 0)
		// 	texX = T_WIDTH - texX - 1;

		// How much to increase the texture coordinate perscreen pixel
		// double step = 1.0 * T_HEIGHT / ray->lineHeight;

		// CEILING
		display_background(data->graphics.hex_ceiling, &bite, 0, ray->drawStart, x); // 13:35 - COMPILED AND RUN : OK
		// int y = 0;
		// while (y < ray->drawStart)
		// {
		// // my_mlx_pixel_put(&bite, x, y, 0xFFFF00);
		// 	my_mlx_pixel_put(&bite, x, y, data->graphics.hex_ceiling);
		// 	y++;
		// }

		// Starting texture coordinate
		display_wall_textures(data, ray, &bite, x);
		// for (int y = ray->drawStart; y < ray->drawEnd; y++)
		// {
		// 	int color;
		// 	int	r;
		// 	int	g;
		// 	int	b;
		// 	r = data->tex.no.addr[(int)(ray->wallX * T_WIDTH) * (data->tex.no.bits_per_pixel >> 3)
		// 		+ 2 + (int)((y - ray->drawStart * 1.0) / ray->lineHeight
		// 			* T_HEIGHT) * data->tex.no.line_length];
		// 	g = data->tex.no.addr[(int)(ray->wallX * T_WIDTH) * (data->tex.no.bits_per_pixel >> 3)
		// 		+ 1 + (int)((y - ray->drawStart * 1.0)
		// 			/ ray->lineHeight * T_HEIGHT) *data->tex.no.line_length];
		// 	b = data->tex.no.addr[(int)(ray->wallX * T_WIDTH) * (data->tex.no.bits_per_pixel >> 3)
		// 		+ (int)((y - ray->drawStart * 1.0)
		// 			/ ray->lineHeight * T_HEIGHT) *data->tex.no.line_length];
		// 	color = rgb_to_hex(r, g, b);
		// 	// make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		// 	if (ray->side == 1)
		// 		color = (color >> 1) & 8355711;
		// 	my_mlx_pixel_put(&bite, x, y, color);
		// }

		// FLOOR
		// y = ray->drawEnd;
		// while (y < W_HEIGHT) {
		// my_mlx_pixel_put(&bite, x, y, data->graphics.hex_floor);
		// y++;
		// }
		display_background(data->graphics.hex_floor, &bite, ray->drawEnd, W_HEIGHT, x);
		x++;
	}

	mlx_put_image_to_window(data->mlx, data->win, bite.mlx_img, 0, 0);
	
	if (data->img.mlx_img)
	{
		mlx_destroy_image(data->mlx, data->img.mlx_img);
	}
	data->img.mlx_img = bite.mlx_img;
	data->img.addr =  bite.addr;
}

int	raycasting_loop(t_data *data)
{
	calc(data);
	// mlx_put_image_to_window(info->mlx, info->win, &info->img, 0, 0);

	return (0);
}