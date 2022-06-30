/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 17:18:51 by tmanolis          #+#    #+#             */
/*   Updated: 2022/06/30 20:11:40 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_graphics(t_graphics *graphics)
{
	graphics->dir_no = NULL;
	graphics->dir_so = NULL;
	graphics->dir_we = NULL;
	graphics->dir_ea = NULL;
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
