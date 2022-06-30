#include "cub3d.h"

double	player_offset(t_data *data, char letter)
{
	double	result;

	result = PLAYER_SIZE;
	if ((letter == 'X' && data->map.dir_x < 0)
		|| (letter == 'Y' && data->map.dir_y < 0))
	{	
		result = PLAYER_SIZE * -1;
		printf("result : %f\n", result);
		return (result);
	}
	return (result);
}

// Pattern : "+" symbols everywhere
void	move_forward(t_data *data)
{
	double x1;
	double y1;
	double x2;
	double y2;
	
	y1 = (data->map.pos_x + data->map.dir_x * data->map.move_speed + player_offset(data, 'X'));
	x1 = (data->map.pos_y + player_offset(data, 'Y'));
	y2 = (data->map.pos_x + player_offset(data, 'X'));
	x2 = (data->map.pos_y + data->map.dir_y * data->map.move_speed + player_offset(data, 'Y'));
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

	// UPDATE VALUE OF POS_X
	y = (data->map.pos_x - data->map.dir_x * data->map.move_speed); // + player_offset(data, 'X'));
	x = data->map.pos_y; // + player_offset(data, 'Y');
	if (data->map.map_marc[(int)x][(int)y] != WALL)
		data->map.pos_x -= data->map.dir_x * data->map.move_speed;
	// UPDATE VALUE OF POS_Y
	y = (data->map.pos_x); // + player_offset(data, 'X');
	x = (data->map.pos_y + data->map.dir_y * data->map.move_speed); // + player_offset(data, 'Y');
	if (data->map.map_marc[(int)x][(int)y] != WALL)
		data->map.pos_y -= data->map.dir_y * data->map.move_speed;
}

// Pattern : "-" and then "+" 
void	move_left(t_data *data)
{
	double x1;
	double y1;
	double x2;
	double y2;
	// double p_size1 = PLAYER_SIZE;
	// if (data->map.dir_x < 0)
	// 	p_size1 = -p_size1;
	// double p_size2 = PLAYER_SIZE;
	// if (data->map.dir_y < 0)
	// 	p_size2 = -p_size2;

	y1 = (data->map.pos_x - data->map.dir_x * data->map.move_speed)+ player_offset(data, 'X');
	x1 = (data->map.pos_y) + player_offset(data, 'Y');
	y2 = (data->map.pos_x) + player_offset(data, 'X');
	x2 = (data->map.pos_y + data->map.dir_y * data->map.move_speed) + player_offset(data, 'Y');
	if (data->map.map_marc[(int)x1][(int)y1] != WALL)
		data->map.pos_x -= data->map.dir_y * data->map.move_speed;
	if (data->map.map_marc[(int)x2][(int)y2] != WALL)
		data->map.pos_y += data->map.dir_x * data->map.move_speed;
}

// Pattern : "+" and then "-"
void	move_right(t_data *data)
{
	double x1;
	double y1;
	double x2;
	double y2;
	// double p_size1 = PLAYER_SIZE;
	// if (data->map.dir_x < 0)
	// 	p_size1 = -p_size1;
	// double p_size2 = PLAYER_SIZE;
	// if (data->map.dir_y < 0)
	// 	p_size2 = -p_size2;

	y1 = (data->map.pos_x + data->map.dir_x * data->map.move_speed); // + player_offset(data, 'X');
	x1 = data->map.pos_y; // + player_offset(data, 'Y');
	y2 = data->map.pos_x ; //+ player_offset(data, 'X');
	x2 = (data->map.pos_y - data->map.dir_y * data->map.move_speed); // + player_offset(data, 'Y');
	if (data->map.map_marc[(int)x1][(int)y1] != WALL)
			data->map.pos_x += data->map.dir_y * data->map.move_speed;
	if (data->map.map_marc[(int)x2][(int)y2] != WALL)
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