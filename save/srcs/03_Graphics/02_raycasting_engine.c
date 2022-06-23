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


void	verLine(t_img *img, int x, int y1, int y2, int color)
{
	int	y = 0;
	int sky = 0xFFFF00;
	int floor = BLACK; 

	while (y < y1) {
		my_mlx_pixel_put(img, x, y, sky);
		y++;
	}
	y = y1;

	while (y <= y2)
	{
		my_mlx_pixel_put(img, x, y, color);
//		mlx_pixel_put(data->mlx, data->win, x, y, color);
		y++;
	}
	while (y < W_HEIGHT) {
		my_mlx_pixel_put(img, x, y, floor);
		y++;
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

	bite.mlx_img = mlx_new_image(data->mlx, data->win_width, data->win_height);
	bite.addr = mlx_get_data_addr(bite.mlx_img, &data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
	bite.line_length = data->img.line_length;
	bite.endian= data->img.endian;
	bite.bits_per_pixel= data->img.bits_per_pixel;

	while (x < data->win_width)
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
		// int side; //was a NS or a EW wall hit?

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

		while (ray->hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (ray->sideDistX < ray->sideDistY)
			{
				ray->sideDistX += ray->deltaDistX;
				ray->mapX += ray->stepX;
				ray->side = 0;
			}
			else
			{
				ray->sideDistY += ray->deltaDistY;
				ray->mapY += ray->stepY;
				ray->side = 1;
			}
			//Check if ray has hit a wall
			
			if (worldMap[ray->mapX][ray->mapY] == 1) 
				ray->hit = 1;
			// else if (worldMap[mapX][mapY] == 2)
			// {
			// 	printf("boucle hit : %d\n", worldMap[mapX][mapY]);
			// 	hit = 1;
			// }
		}
		if (ray->side == 0)
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

		// // int	color;
		// // printf("je tombe sur cette valeur : %c\n", worldMap[mapX][mapY]);
		// if (worldMap[ray->mapX][ray->mapY] == 1)
		// 	ray->color = PINK; // rouge
		// // else if (map->map[mapX][mapY] == '2')
		// // 	color = 0x00FF00;  // vert
		// // else if (map->map[mapX][mapY] == 3)
		// // 	color = 0x0000FF; // bleu
		// // else if (map->map[mapX][mapY] == 4)
		// // 	color = 0xFFFFFF; // white
		// // else if (map->map[mapX][mapY] == 5)
		// // 	color = 0xFFFF00; // jaune
		// else
		// 	ray->color = PURPLE;
		// if (ray->side == 1)
		// 	ray->color = ray->color / 2;

		// verLine(&bite, x, ray->drawStart, ray->drawEnd, ray->color);
		
		double wallX;
		if (ray->side == 0)
			wallX = map->pos_y + ray->perpWallDist * ray->rayDirY;
		else
			wallX = map->pos_x + ray->perpWallDist * ray->rayDirX;
		wallX -= floor(wallX);

		// x coordinate on the texture
		int texX = (int)(wallX * (double)T_WIDTH);
		if (ray->side == 0 && ray->rayDirX > 0)
			texX = T_WIDTH - texX - 1;
		if (ray->side == 1 && ray->rayDirY < 0)
			texX = T_WIDTH - texX - 1;

		// How much to increase the texture coordinate perscreen pixel
		double step = 1.0 * T_HEIGHT / ray->lineHeight;

		// CEILING
		int y = 0;
		while (y < ray->drawStart)
		{
		// my_mlx_pixel_put(&bite, x, y, 0xFFFF00);
			my_mlx_pixel_put(&bite, x, y, data->graphics.hex_ceiling);
			y++;
		}
		// Starting texture coordinate
		// TODO: le calcul de texPos diff du code de Satcheen a checker
		// double texPos = (ray->drawStart - W_HEIGHT / 2 + ray->lineHeight / 2) * step;
		for (int y = ray->drawStart; y < ray->drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (T_HEIGHT - 1) in case of overflow
			// int texY = (int)texPos & (T_HEIGHT - 1);
			// texPos += step;
			// int color = data->tex.no.addr[T_WIDTH * texY + texX];
			int color;
			int	r;
			int	g;
			int	b;
			r = data->tex.no.addr[(int)(wallX * T_WIDTH) * (data->tex.no.bits_per_pixel >> 3)
				+ 2 + (int)((y - ray->drawStart * 1.0) / ray->lineHeight
					* T_HEIGHT) * data->tex.no.line_length];
			g = data->tex.no.addr[(int)(wallX * T_WIDTH) * (data->tex.no.bits_per_pixel >> 3)
				+ 1 + (int)((y - ray->drawStart * 1.0)
					/ ray->lineHeight * T_HEIGHT) *data->tex.no.line_length];
			b = data->tex.no.addr[(int)(wallX * T_WIDTH) * (data->tex.no.bits_per_pixel >> 3)
				+ (int)((y - ray->drawStart * 1.0)
					/ ray->lineHeight * T_HEIGHT) *data->tex.no.line_length];
			color = rgb_to_hex(r, g, b);
			// // make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if (ray->side == 1)
				color = (color >> 1) & 8355711;

			my_mlx_pixel_put(&bite, x, y, color);
		}
		// FLOOR
		y = ray->drawEnd;
		while (y < W_HEIGHT) {
		my_mlx_pixel_put(&bite, x, y, data->graphics.hex_floor);
		y++;
		}
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