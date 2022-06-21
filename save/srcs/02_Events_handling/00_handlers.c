#include "cub3d.h"

int	handle_crossbtn(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	data->win = NULL;
	mlx_destroy_display(data->mlx);
	free_for_your_life(data);
	exit(0);
	return (0);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx, data->win);
		data->win = NULL;
		printf("j'ai fait le taff\n");
		mlx_destroy_display(data->mlx);
		free_for_your_life(data);
		exit(0);
	}
	else if (ft_strchr("wasd", keysym))
		move_player(data, keysym);
	return (0);
}

int	render(t_data *data)
{
	// raycast(data);
	// draw_line(data.mlx, data.win, W_WIDTH, W_HEIGHT, 0, 0, 0xFFFFFF);
	draw_the_2d_map(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.mlx_img, -1, W_HEIGHT - 24 * CELL_SIZE);

	return (0);
}

int	key_press(int keysym, t_data *data)
{
	double old_dir_x;
	double old_plane_x;

	printf("Touche appuyée : %c\n", keysym);
	printf("Avant déplacement -> X: %f | Y : %f\n", data->map.pos_x, data->map.pos_y);
	old_dir_x = data->map.dir_x;
	old_plane_x = data->map.plane_x;
	if (keysym == 'w')
	{
		if (data->map.map[(int)(data->map.pos_x + data->map.dir_x * data->map.move_speed)][(int)data->map.pos_y] != '1')
			data->map.pos_x += data->map.dir_x * data->map.move_speed;
		if (data->map.map[(int)(data->map.pos_x)][(int)(data->map.pos_y + data->map.dir_y * data->map.move_speed)] != '1')
			data->map.pos_y += data->map.dir_y * data->map.move_speed;

	}
	if (keysym == 's')
	{
		if (data->map.map[(int)(data->map.pos_x - data->map.dir_x * data->map.move_speed)][(int)(data->map.pos_y)] != '1')
			data->map.pos_x -= data->map.dir_x * data->map.move_speed;
		if (data->map.map[(int)(data->map.pos_x)][(int)(data->map.pos_y + data->map.dir_y * data->map.move_speed)] != '1')
			data->map.pos_y -= data->map.dir_y * data->map.move_speed;
	}
	// BUG: trouver une maniere plus organique de changer la valeur du dir_y. x pas sensé bouger
	if (keysym == 'a')
	{
		printf("Valeur de dir_y : %f\n", data->map.dir_y);
		if (data->map.map[(int)(data->map.pos_x - data->map.dir_x * data->map.move_speed)][(int)(data->map.pos_y)] != '1')
			data->map.pos_x -= data->map.dir_y * data->map.move_speed;
		if (data->map.map[(int)(data->map.pos_x)][(int)(data->map.pos_y + data->map.dir_y * data->map.move_speed)] != '1')
			data->map.pos_y += data->map.dir_x * data->map.move_speed;
	}
	if (keysym == 'd')
	{
		if (data->map.map[(int)(data->map.pos_x + data->map.dir_x * data->map.move_speed)][(int)(data->map.pos_y)] != '1')
			data->map.pos_x += data->map.dir_y * data->map.move_speed;
		if (data->map.map[(int)(data->map.pos_x)][(int)(data->map.pos_y - data->map.dir_y * data->map.move_speed)] != '1')
			data->map.pos_y -= data->map.dir_x * data->map.move_speed;
	}
	//rotate to the right
	if (keysym == ARROW_RIGHT)
	{
		//both camera direction and camera plane must be rotated
		data->map.dir_x = data->map.dir_x * cos(-data->map.rotate_speed) - data->map.dir_y * sin(-data->map.rotate_speed);
		data->map.dir_y = old_dir_x * sin(-data->map.rotate_speed) + data->map.dir_y * cos(-data->map.rotate_speed);
		data->map.plane_x = data->map.plane_x * cos(-data->map.rotate_speed) - data->map.plane_y * sin(-data->map.rotate_speed);
		data->map.plane_y = old_plane_x * sin(-data->map.rotate_speed) + data->map.plane_y * cos(-data->map.rotate_speed);
	}
	//rotate to the left
	if (keysym == ARROW_LEFT)
	{
		//both camera direction and camera plane must be rotated
		data->map.dir_x = data->map.dir_x * cos(data->map.rotate_speed) - data->map.dir_y * sin(data->map.rotate_speed);
		data->map.dir_y = old_dir_x * sin(data->map.rotate_speed) + data->map.dir_y * cos(data->map.rotate_speed);
		data->map.plane_x = data->map.plane_x * cos(data->map.rotate_speed) - data->map.plane_y * sin(data->map.rotate_speed);
		data->map.plane_y = old_plane_x * sin(data->map.rotate_speed) + data->map.plane_y * cos(data->map.rotate_speed);
	}
	printf("Après déplacement -> X: %f | Y : %f\n", data->map.pos_x, data->map.pos_y);
	// raycasting_loop(data);
	return (0);
}