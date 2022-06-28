#include "cub3d.h"

// Pattern : "+" symbols everywhere
void	move_forward(t_data *data)
{
	int	y1;
	int	x1;
	int	y2;
	int	x2;

	y1 = (int)(data->map.pos_x + data->map.dir_x * data->map.move_speed);
	x1 = (int)data->map.pos_y;
	y2 = (int)(data->map.pos_x);
	x2 = (int)(data->map.pos_y + data->map.dir_y * data->map.move_speed);
	if (data->map.map[y1][x1] != WALL)
		data->map.pos_x += data->map.dir_x * data->map.move_speed;
	if (data->map.map[y2][x2] != WALL)
		data->map.pos_y += data->map.dir_y * data->map.move_speed;
}

// Pattern : "-" symbols everywhere 
void	move_backward(t_data *data)
{
	int	y;
	int	x;

	// UPDATE VALUE OF POS_X
	y = (int)(data->map.pos_x - data->map.dir_x * data->map.move_speed);
	x = (int)data->map.pos_y;
	if (data->map.map[y][x] != WALL)
		data->map.pos_x -= data->map.dir_x * data->map.move_speed;
	// UPDATE VALUE OF POS_Y
	y = (int)(data->map.pos_x);
	x = (int)(data->map.pos_y + data->map.dir_y * data->map.move_speed);
	if (data->map.map[y][x] != WALL)
		data->map.pos_y -= data->map.dir_y * data->map.move_speed;
}

// Pattern : "-" and then "+" 
void	move_left(t_data *data)
{
	int	y1;
	int	x1;
	int	y2;
	int	x2;

	y1 = (int)(data->map.pos_x - data->map.dir_x * data->map.move_speed);
	x1 = (int)(data->map.pos_y);
	y2 = (int)(data->map.pos_x);
	x2 = (int)(data->map.pos_y + data->map.dir_y * data->map.move_speed);
	if (data->map.map[y1][x1] != WALL)
		data->map.pos_x -= data->map.dir_y * data->map.move_speed;
	if (data->map.map[y2][x2] != WALL)
		data->map.pos_y += data->map.dir_x * data->map.move_speed;
}

// Pattern : "+" and then "-"
void	move_right(t_data *data)
{
	int	y1;
	int	x1;
	int	y2;
	int	x2;

	y1 = (int)(data->map.pos_x + data->map.dir_x * data->map.move_speed);
	x1 = (int)(data->map.pos_y);
	y2 = (int)(data->map.pos_x);
	x2 = (int)(data->map.pos_y - data->map.dir_y * data->map.move_speed);
	if (data->map.map[y1][x1] != WALL)
			data->map.pos_x += data->map.dir_y * data->map.move_speed;
	if (data->map.map[y2][x2] != WALL)
		data->map.pos_y -= data->map.dir_x * data->map.move_speed;
}

// Same function for both left and right rotations, only the value (pos or neg)
// of the speed changes.
void	rotate_sight(t_data *data, double ro_speed)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = data->map.dir_x;
	old_plane_x = data->map.plane_x;
	data->map.dir_x = data->map.dir_x * cos(ro_speed) - data->map.dir_y * sin(ro_speed);
	data->map.dir_y = old_dir_x * sin(ro_speed) + data->map.dir_y * cos(ro_speed);
	data->map.plane_x = data->map.plane_x * cos(ro_speed) - data->map.plane_y * sin(ro_speed);
	data->map.plane_y = old_plane_x * sin(ro_speed) + data->map.plane_y * cos(ro_speed);
}