#include "cub3d.h"

void	init_raycasting_variables(t_data *data, t_raycast *ray, t_map *map, int x)
{
	ray->cameraX = 2 * x / (double)data->win_width - 1;
	ray->rayDirX = map->dir_x + map->plane_x * ray->cameraX;
	ray->rayDirY = map->dir_y + map->plane_y * ray->cameraX;
	ray->mapX = (int)map->pos_x;
	ray->mapY = (int)map->pos_y;
	ray->deltaDistX = fabs(1 / ray->rayDirX);
	ray->deltaDistY = fabs(1 / ray->rayDirY);
	ray->hit = 0; 
}

void	calculate_raydirx_and_stepx(t_raycast *ray, t_map *map)
{
	if (ray->rayDirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (map->pos_x - ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - map->pos_x) * ray->deltaDistX;
	}
	if (ray->rayDirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (map->pos_y - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - map->pos_y) * ray->deltaDistY;
	}
}

// LE PB : ca segfault quand on arrive a la lettre du joueur
void	which_distance_if_wall_hit(t_raycast *ray, t_map *map)
{
	while (ray->hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			ray->side = (ray->rayDirX > 0) ? EA : WE;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = (ray->rayDirY > 0) ? SO : NO;
		}
		if (map->map_marc[ray->mapY][ray->mapX] == '1')
			ray->hit = 1;
	}
}

void	calculate_wall_specs(t_data *data, t_raycast *ray, t_map *map)
{
	if (ray->side == EA || ray->side == WE)
		ray->perpWallDist = (ray->mapX - map->pos_x + (1 - ray->stepX) / 2) / ray->rayDirX;
	else
		ray->perpWallDist = (ray->mapY - map->pos_y + (1 - ray->stepY) / 2) / ray->rayDirY;
	ray->lineHeight = (int)(data->win_height / ray->perpWallDist);
	ray->drawStart = -(ray->lineHeight) / 2 + data->win_height / 2;
	// if(ray->drawStart < 0)
	// 	ray->drawStart = 0;
	ray->drawEnd = ray->lineHeight / 2 + data->win_height / 2;
	if(ray->drawEnd >= data->win_height)
		ray->drawEnd = data->win_height - 1;
	if (ray->side == EA || ray->side == WE)
		ray->wallX = map->pos_y + ray->perpWallDist * ray->rayDirY;
	else
		ray->wallX = map->pos_x + ray->perpWallDist * ray->rayDirX;
	ray->wallX -= floor(ray->wallX);
}
