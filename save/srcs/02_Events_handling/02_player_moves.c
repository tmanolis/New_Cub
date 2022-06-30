/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_player_moves.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 17:58:38 by msanjuan          #+#    #+#             */
/*   Updated: 2022/06/30 18:48:47 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Pattern : "+" symbols everywhere
void	move_forward(t_data *data)
{
	double	x1;
	double	y1;
	double	x2;
	double	y2;

	y1 = (data->map.pos_x + data->map.dir_x * data->map.move_speed
			+ player_offset(data, 'X'));
	x1 = (data->map.pos_y + player_offset(data, 'Y'));
	y2 = (data->map.pos_x + player_offset(data, 'X'));
	x2 = (data->map.pos_y + data->map.dir_y * data->map.move_speed
			+ player_offset(data, 'Y'));
	if (data->map.map_marc[(int)x1][(int)y1] != WALL)
		data->map.pos_x += data->map.dir_x * data->map.move_speed;
	if (data->map.map_marc[(int)x2][(int)y2] != WALL)
		data->map.pos_y += data->map.dir_y * data->map.move_speed;
}

// Pattern : "-" symbols everywhere 
void	move_backward(t_data *data)
{
	double	y;
	double	x;

	y = (data->map.pos_x - data->map.dir_x * data->map.move_speed);
	x = data->map.pos_y;
	if (data->map.map_marc[(int)x][(int)y] != WALL)
		data->map.pos_x -= data->map.dir_x * data->map.move_speed;
	y = (data->map.pos_x);
	x = (data->map.pos_y + data->map.dir_y * data->map.move_speed);
	if (data->map.map_marc[(int)x][(int)y] != WALL)
		data->map.pos_y -= data->map.dir_y * data->map.move_speed;
}

// Pattern : "-" and then "+" 
void	move_left(t_data *data)
{
	double	x1;
	double	y1;
	double	x2;
	double	y2;

	y1 = (data->map.pos_x - data->map.dir_x * data->map.move_speed)
		+ player_offset(data, 'X');
	x1 = (data->map.pos_y) + player_offset(data, 'Y');
	y2 = (data->map.pos_x) + player_offset(data, 'X');
	x2 = (data->map.pos_y + data->map.dir_y * data->map.move_speed)
		+ player_offset(data, 'Y');
	if (data->map.map_marc[(int)x1][(int)y1] != WALL)
		data->map.pos_x -= data->map.dir_y * data->map.move_speed;
	if (data->map.map_marc[(int)x2][(int)y2] != WALL)
		data->map.pos_y += data->map.dir_x * data->map.move_speed;
}

// Pattern : "+" and then "-"
void	move_right(t_data *data)
{
	double	x1;
	double	y1;
	double	x2;
	double	y2;

	y1 = (data->map.pos_x + data->map.dir_x * data->map.move_speed);
	x1 = data->map.pos_y;
	y2 = data->map.pos_x ;
	x2 = (data->map.pos_y - data->map.dir_y * data->map.move_speed);
	if (data->map.map_marc[(int)x1][(int)y1] != WALL)
			data->map.pos_x += data->map.dir_y * data->map.move_speed;
	if (data->map.map_marc[(int)x2][(int)y2] != WALL)
		data->map.pos_y -= data->map.dir_x * data->map.move_speed;
}

// Same function for both left and right rotations, only the value (pos or neg)
// of the speed changes.
void	rotate_sight(t_data *data, double ro_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->map.dir_x;
	old_plane_x = data->map.plane_x;
	data->map.dir_x = data->map.dir_x * cos(ro_speed)
		- data->map.dir_y * sin(ro_speed);
	data->map.dir_y = old_dir_x * sin(ro_speed) + data->map.dir_y
		* cos(ro_speed);
	data->map.plane_x = data->map.plane_x * cos(ro_speed)
		- data->map.plane_y * sin(ro_speed);
	data->map.plane_y = old_plane_x * sin(ro_speed)
		+ data->map.plane_y * cos(ro_speed);
}
