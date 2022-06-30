/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_init_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmanolis <tmanolis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 18:07:38 by tmanolis          #+#    #+#             */
/*   Updated: 2022/06/30 18:08:40 by tmanolis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_window(t_data *data)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		return (FAILURE);
	data->win = mlx_new_window(data->mlx, data->win_width,
			data->win_height, TITLE);
	if (data->win == NULL)
	{
		free(data->win);
		return (FAILURE);
	}
	data->img.mlx_img = mlx_new_image(data->mlx, W_WIDTH, W_HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, \
		&data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
	return (SUCCESS);
}

void	init_img_to_display(t_data *data, t_img *img)
{
	img->mlx_img = mlx_new_image(data->mlx, data->win_width, data->win_height);
	img->addr = mlx_get_data_addr(img->mlx_img, &data->img.bits_per_pixel, \
		&data->img.line_length, &data->img.endian);
	img->line_length = data->img.line_length;
	img->endian = data->img.endian;
	img->bits_per_pixel = data->img.bits_per_pixel;
}
