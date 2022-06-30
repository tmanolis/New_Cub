#include "cub3d.h"

void	free_double_array(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	if (tab)
	{
		free(tab);
		tab = NULL;
	}
}

static void	free_graphics(t_graphics *graphics)
{
	if (graphics->dir_NO)
		free(graphics->dir_NO);
	if (graphics->dir_SO)
		free(graphics->dir_SO);
	if (graphics->dir_WE)
		free(graphics->dir_WE);
	if (graphics->dir_EA)
		free(graphics->dir_EA);
	if (graphics->floor)
		free(graphics->floor);
	if (graphics->ceiling)
		free(graphics->ceiling);
}

static void	free_map(t_map *map)
{
	if (map->fd > 0)
		close(map->fd);
	if (map->file)
		free_double_array(map->file);
	if (map->map)
		free_double_array(map->map);
	if (map->map_marc)
		free_double_array(map->map_marc);
}


void	free_textures(t_data *data, t_tex tex)
{
	if (tex.no.mlx_img)
		mlx_destroy_image(data->mlx, tex.no.mlx_img);
	if (tex.so.mlx_img)
		mlx_destroy_image(data->mlx, tex.so.mlx_img);
	if (tex.ea.mlx_img)
		mlx_destroy_image(data->mlx, tex.ea.mlx_img);
	if (tex.we.mlx_img)
		mlx_destroy_image(data->mlx, tex.we.mlx_img);
}

int	free_for_your_life(t_data *data)
{
	free_graphics(&data->graphics);
	free_map(&data->map);
	// if (data->mlx)
	// 	free(data->mlx);
	return (FAILURE);
}