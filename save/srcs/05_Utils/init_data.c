/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmanolis <tmanolis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 17:18:51 by tmanolis          #+#    #+#             */
/*   Updated: 2022/06/30 19:50:15 by tmanolis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_graphics(t_graphics *graphics)
{
	graphics->dir_NO = NULL;
	graphics->dir_SO = NULL;
	graphics->dir_WE = NULL;
	graphics->dir_EA = NULL;
	graphics->floor = 0;
	graphics->ceiling = 0;
}

void	init_map(t_map *map)
{
	map->fd = 0;
	map->path = NULL;
	map->file = NULL;
	map->map = NULL;
}

void	init_data(t_data *data)
{
	ft_memset(&data->map, 0, sizeof(t_map));
	init_graphics(&data->graphics);
	init_map(&data->map);
	ft_memset(&data->tex, 0, sizeof(t_tex));
	ft_memset(&data->ray, 0, sizeof(t_raycast));
	data->win_height = W_HEIGHT;
	data->win_width = W_WIDTH;
}
