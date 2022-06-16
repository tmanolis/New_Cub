#include "cub3d.h"

void	rotate_left_or_right(t_data *data, float rotate_speed)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = data->map.dir_x;
	old_plane_x = data->map.plane_x;

	data->map.dir_x = data->map.dir_x * cos(rotate_speed) - data->map.dir_y * sin(rotate_speed);
	data->map.dir_y = old_dir_x * sin(rotate_speed) + data->map.dir_y * cos(rotate_speed);

	data->map.plane_x = data->map.plane_x * cos(rotate_speed) - data->map.plane_y * sin(rotate_speed);
	data->map.plane_y = old_plane_x * sin(rotate_speed) + data->map.plane_y * cos(rotate_speed);
}

/**
 * @brief Checks before moving if the next move is possible, aka, prevent
 * 		  the player from "walking on walls"
 * 
 * @param data 
 * @param keysym The key pressed (up, down, right or left moves)
 * @param x 
 * @param y 
 */
bool	check_collision_with_wall(t_data *data, int keysym, int x, int y)
{
	int	a_x;
	int	d_x;
	int	w_y;
	int	s_y;

	a_x = data->map.p_x + data->map.dir_x * data->map.move_speed;
	d_x = data->map.p_x - data->map.dir_x * data->map.move_speed;
	w_y = data->map.p_y - data->map.dir_y * data->map.move_speed;
	s_y = data->map.p_y + data->map.dir_y * data->map.move_speed;
	if (keysym == 'a' && data->map.map[y][a_x] == '1')
		return (true);
	else if (keysym == 'd' && data->map.map[y][d_x] == '1')
		return (true);
	else if (keysym == 'w' && data->map.map[w_y][x] == '1')
		return (true);
	else if (keysym == 's' && data->map.map[s_y][x] == '1')
		return (true);
	else
		return (false);
}

void	move_player(t_data *data, int keysym)
{
	int	old_dir_x;
	int	old_dir_y;

	old_dir_x = data->map.p_x;
	old_dir_y = data->map.p_y;
	if (check_collision_with_wall(data, keysym, old_dir_x, old_dir_y) == true)
		return ;
	if (keysym == ARROW_LEFT || keysym == ARROW_RIGHT)
	{
		if (keysym == ARROW_LEFT)
			rotate_left_or_right(data, data->map.rotate_speed);	
		if (keysym == ARROW_RIGHT) 
			rotate_left_or_right(data, -data->map.rotate_speed);
	}
	else if (keysym == 'a')
		data->map.p_x += data->map.dir_x * data->map.move_speed;
	else if (keysym == 'd')
		data->map.p_x -= data->map.dir_x * data->map.move_speed;
	else if (keysym == 'w')
		data->map.p_y -= data->map.dir_y * data->map.move_speed;
	else if (keysym == 's')
		data->map.p_y += data->map.dir_y * data->map.move_speed;
	draw_a_cell(data, old_dir_x * CELL_SIZE, old_dir_y * CELL_SIZE, CELL_SIZE,\
	CELL_SIZE, BLACK);
}