#include "cub3d.h"

void	error_exit(t_data *data, char *str)
{
	printf("Error : %s\n", str);
	// if (data->mlx)
	// 	free_textures(data, data->tex);
	if (data)
		free_for_your_life(data);
	exit (0);
}