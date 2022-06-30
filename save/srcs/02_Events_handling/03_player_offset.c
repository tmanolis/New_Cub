/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_player_offset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 17:58:55 by msanjuan          #+#    #+#             */
/*   Updated: 2022/06/30 18:22:45 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	player_offset(t_data *data, char letter)
{
	double	result;

	result = PLAYER_SIZE;
	if ((letter == 'X' && data->map.dir_x < 0)
		|| (letter == 'Y' && data->map.dir_y < 0))
	{	
		result = PLAYER_SIZE * -1;
		return (result);
	}
	return (result);
}
