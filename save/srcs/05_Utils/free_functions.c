/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 17:25:05 by tmanolis          #+#    #+#             */
/*   Updated: 2022/06/30 20:11:40 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (graphics->dir_no)
		free(graphics->dir_no);
	if (graphics->dir_so)
		free(graphics->dir_so);
	if (graphics->dir_we)
		free(graphics->dir_we);
	if (graphics->dir_ea)
		free(graphics->dir_ea);
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
	return (FAILURE);
}
