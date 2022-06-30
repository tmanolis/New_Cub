/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_raycasting_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 18:15:01 by tmanolis          #+#    #+#             */
/*   Updated: 2022/06/30 20:18:33 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_raycasting_var(t_data *data, t_raycast *ray, t_map *map, int x)
{
	ray->camera_x = 2 * x / (double)data->win_width - 1;
	ray->raydir_x = map->dir_x + map->plane_x * ray->camera_x;
	ray->raydir_y = map->dir_y + map->plane_y * ray->camera_x;
	ray->mapx = (int)map->pos_x;
	ray->mapy = (int)map->pos_y;
	ray->deltadist_x = fabs(1 / ray->raydir_x);
	ray->deltadist_y = fabs(1 / ray->raydir_y);
	ray->hit = 0;
}

void	calculate_raydir_x_and_step_x(t_raycast *ray, t_map *map)
{
	if (ray->raydir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (map->pos_x - ray->mapx) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->mapx + 1.0 - map->pos_x) * ray->deltadist_x;
	}
	if (ray->raydir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (map->pos_y - ray->mapy) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->mapy + 1.0 - map->pos_y) * ray->deltadist_y;
	}
}

void	which_distance_if_wall_hit(t_raycast *ray, t_map *map)
{
	while (ray->hit == 0)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->mapx += ray->step_x;
			if (ray->raydir_x > 0)
				ray->side = EA;
			else
				ray->side = WE;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->mapy += ray->step_y;
			if (ray->raydir_y > 0)
				ray->side = SO;
			else
				ray->side = NO;
		}
		if (map->map_marc[ray->mapy][ray->mapx] == '1')
			ray->hit = 1;
	}
}

void	calculate_wall_specs(t_data *data, t_raycast *ray, t_map *map)
{
	if (ray->side == EA || ray->side == WE)
		ray->wall_dist = (ray->mapx - map->pos_x + (1 - ray->step_x) / 2) \
		/ ray->raydir_x;
	else
		ray->wall_dist = (ray->mapy - map->pos_y + (1 - ray->step_y) / 2) \
		/ ray->raydir_y;
	ray->line_height = (int)(data->win_height / ray->wall_dist);
	ray->draw_start = -(ray->line_height) / 2 + data->win_height / 2;
	ray->draw_end = ray->line_height / 2 + data->win_height / 2;
	if (ray->draw_end >= data->win_height)
		ray->draw_end = data->win_height - 1;
	if (ray->side == EA || ray->side == WE)
		ray->wall_x = map->pos_y + ray->wall_dist * ray->raydir_y;
	else
		ray->wall_x = map->pos_x + ray->wall_dist * ray->raydir_x;
	ray->wall_x -= floor(ray->wall_x);
}
