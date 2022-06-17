#include "cub3d.h"

int	load_xpm(t_data *data, char *path, int *tex_buf, t_img *img)
{
	// remplit taille img et ca a cree un pointeur void mlximg
	img->mlx_img = mlx_xpm_file_to_image(data->mlx, path, &img->x, &img->y);
	// NOTE: si on veut faire un truc propre, on aura une meilleure resolution
	// avec un cast sur le retour de la fonction addr (int *)
	img->addr = mlx_get_data_addr(img->mlx_img, &img->bits_per_pixel, &img->line_length, &img->endian);
	// on est donc alle chercher notre tex, et on a recup touts le sinfos de la text dans mlx_img

	int	y;
	int	x;

	y = 0;
	while (y < img->y)
	{
		
		x = 0;
		while (x < img->x)
		{
			tex_buf[y * 64 + x] = (int)img->addr[y * 64 + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(data->mlx, img->mlx_img);
	return (SUCCESS);
}	

int	init_textures(t_data *data)
{
	t_img img;
	// malloc le int
	data->tex.no = (int *)malloc(sizeof(int) * T_HEIGHT * T_WIDTH);
	data->tex.so = (int *)malloc(sizeof(int) * T_HEIGHT * T_WIDTH);
	data->tex.we = (int *)malloc(sizeof(int) * T_HEIGHT * T_WIDTH);
	data->tex.ea = (int *)malloc(sizeof(int) * T_HEIGHT * T_WIDTH);
	
	load_xpm(data, "assets/wood.xpm", data->tex.no, &img);
	load_xpm(data, data->graphics.dir_SO, data->tex.so, &img);
	load_xpm(data, data->graphics.dir_WE, data->tex.we, &img);
	load_xpm(data, data->graphics.dir_EA, data->tex.ea, &img);
	// TODO: penser à proteger malloc toussa
	return (SUCCESS);
}

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