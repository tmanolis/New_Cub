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

void	free_graphics(t_graphics *graphics)
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

void	free_map(t_map *map)
{
	if (map->fd > 0)
		close(map->fd);
	if (map->file)
		free_double_array(map->file);
	if (map->map)
		free_double_array(map->map);
}

int	free_for_your_life(t_data *data)
{
	free_graphics(&data->graphics);
	free_map(&data->map);
	if (data->mlx)
		free(data->mlx);
	return (FAILURE);
}