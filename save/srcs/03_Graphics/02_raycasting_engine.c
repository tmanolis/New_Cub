#include "cub3d.h"




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
	t_map	*map;
	int	x;

	map = &data->map;
	x = 0;

	t_img	bite;

	bite.mlx_img = mlx_new_image(data->mlx, data->win_width, data->win_height);
	bite.addr = mlx_get_data_addr(bite.mlx_img, &data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
	bite.line_length = data->img.line_length;
	bite.endian= data->img.endian;
	bite.bits_per_pixel= data->img.bits_per_pixel;

	while (x < data->win_width)
	{
		double cameraX = 2 * x / (double)data->win_width - 1;
		double rayDirX = map->dir_x + map->plane_x * cameraX;
		double rayDirY = map->dir_y + map->plane_y * cameraX;
		
		int mapX = (int)map->pos_x;
		int mapY = (int)map->pos_y;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;
		
		 //length of ray from one x or y-side to next x or y-side
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;
		
		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;
		
		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (map->pos_x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - map->pos_x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (map->pos_y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - map->pos_y) * deltaDistY;
		}

		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			
			if (worldMap[mapX][mapY] == 1) 
				hit = 1;
			// else if (worldMap[mapX][mapY] == 2)
			// {
			// 	printf("boucle hit : %d\n", worldMap[mapX][mapY]);
			// 	hit = 1;
			// }
		}
		if (side == 0)
			perpWallDist = (mapX - map->pos_x + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - map->pos_y + (1 - stepY) / 2) / rayDirY;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(data->win_height / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + data->win_height / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + data->win_height / 2;
		if(drawEnd >= data->win_height)
			drawEnd = data->win_height - 1;

		int	color;
		// printf("je tombe sur cette valeur : %c\n", worldMap[mapX][mapY]);
		if (worldMap[mapX][mapY] == 1)
			color = PINK; // rouge
		// else if (map->map[mapX][mapY] == '2')
		// 	color = 0x00FF00;  // vert
		// else if (map->map[mapX][mapY] == 3)
		// 	color = 0x0000FF; // bleu
		// else if (map->map[mapX][mapY] == 4)
		// 	color = 0xFFFFFF; // white
		// else if (map->map[mapX][mapY] == 5)
		// 	color = 0xFFFF00; // jaune
		else
			color = PURPLE;
		if (side == 1)
			color = color / 2;

		verLine(&bite, x, drawStart, drawEnd, color);
		
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