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
}


// static void	free_textures(t_tex tex)
// {
// 	if (tex.no)
// 		free(tex.no);
// 	if (tex.so)
// 		free(tex.so);
// 	if (tex.ea)
// 		free(tex.ea);
// 	if (tex.we)
// 		free(tex.we);
// }

int	free_for_your_life(t_data *data)
{
	free_graphics(&data->graphics);
	free_map(&data->map);
	if (data->mlx)
		free(data->mlx);
	// free_textures(data->tex);
	return (FAILURE);
}