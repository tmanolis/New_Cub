/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 17:19:25 by tmanolis          #+#    #+#             */
/*   Updated: 2022/06/30 20:20:36 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_player_direction(t_map *map, char dir)
{
	if (dir == 'S')
	{
		map->dir_x = 1;
		map->dir_y = 0;
		map->plane_x = 0.0;
		map->plane_y = -0.66;
	}
	if (dir == 'E')
	{
		map->dir_x = 0;
		map->dir_y = 1;
		map->plane_x = 0.66;
		map->plane_y = 0.0;
	}
	if (dir == 'W')
	{
		map->dir_x = 0;
		map->dir_y = -1;
		map->plane_x = -0.66;
		map->plane_y = 0.00;
	}
}

void	init_raycasting(t_map *map)
{
	map->pos_x = (double)map->p_y + 0.5;
	map->pos_y = (double)map->p_x + 0.5;
	map->dir_x = -1;
	map->dir_y = 0;
	map->plane_x = 0;
	map->plane_y = 0.66;
	set_player_direction(map, map->p_direction);
	map->move_speed = 0.06;
	map->rotate_speed = 0.04;
}
