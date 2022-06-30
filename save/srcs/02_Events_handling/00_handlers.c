/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_handlers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 13:34:25 by msanjuan          #+#    #+#             */
/*   Updated: 2022/06/30 19:52:29 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cross_btn_handler(t_data *data)
{
	if (data->img.mlx_img)
		mlx_destroy_image(data->mlx, data->img.mlx_img);
	mlx_destroy_window(data->mlx, data->win);
	data->win = NULL;
	free_textures(data, data->tex);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free_for_your_life(data);
	exit(0);
	return (0);
}

int	key_press_handler(int keysym, t_data *data)
{
	if (keysym == 'w')
		move_forward(data);
	if (keysym == 's')
		move_backward(data);
	if (keysym == 'a')
		move_left(data);
	if (keysym == 'd')
		move_right(data);
	if (keysym == ARROW_RIGHT)
		rotate_sight(data, data->map.rotate_speed * -1);
	if (keysym == ARROW_LEFT)
		rotate_sight(data, data->map.rotate_speed);
	if (keysym == XK_Escape)
	{
		if (data->img.mlx_img)
			mlx_destroy_image(data->mlx, data->img.mlx_img);
		mlx_destroy_window(data->mlx, data->win);
		data->win = NULL;
		free_textures(data, data->tex);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		free_for_your_life(data);
		exit(0);
	}
	return (SUCCESS);
}

int	raycasting_handler(t_data *data)
{
	t_img	tmp_img;

	init_img_to_display(data, &tmp_img);
	calculate_and_display(data, &tmp_img);
	mlx_put_image_to_window(data->mlx, data->win, tmp_img.mlx_img, 0, 0);
	if (data->img.mlx_img)
		mlx_destroy_image(data->mlx, data->img.mlx_img);
	data->img.mlx_img = tmp_img.mlx_img;
	data->img.addr = tmp_img.addr;
	return (0);
}
