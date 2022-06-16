#include "cub3d.h"

int	init_window(t_data *data)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		return (FAILURE);
	data->win = mlx_new_window(data->mlx, data->win_width,
			data->win_height, TITLE);
	if (data->win == NULL)
	{
		free(data->win);
		return (FAILURE);
	}
	data->img.mlx_img = mlx_new_image(data->mlx, W_WIDTH, W_HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
	return (SUCCESS);
}