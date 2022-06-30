/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 17:57:41 by msanjuan          #+#    #+#             */
/*   Updated: 2022/06/30 17:58:15 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mlx_loop_and_hooks(t_data data)
{
	mlx_loop_hook(data.mlx, &raycasting_handler, &data);
	mlx_hook(data.win, KeyPress, KeyPressMask, &key_press_handler, &data);
	mlx_hook(data.win, ClientMessage, LeaveWindowMask, \
		&cross_btn_handler, &data);
	mlx_loop(data.mlx);
}
