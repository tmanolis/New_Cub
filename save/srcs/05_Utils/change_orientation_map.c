/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_orientation_map.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 19:08:29 by msanjuan          #+#    #+#             */
/*   Updated: 2022/06/30 19:23:41 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	stock_inversed_map(t_data *data, char **map_char, int i)
{
	int	j;
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map_char[y][x])
	{
		j = 0;
		data->map.map_marc[i] = (char *)malloc(sizeof(char)
				* (data->map.nb_line + 1));
		while (y < data->map.nb_line)
		{
			data->map.map_marc[i][j] = map_char[y][x];
			j++;
			y++;
		}
		data->map.map_marc[i][j] = '\0';
		y = 0;
		i++;
		x++;
	}
	data->map.map_marc[i] = NULL;
}

void	change_orientation_map(t_data *data, char **map_char)
{
	int		i;
	int		j;
	size_t	biggest_len;

	i = 0;
	j = 0;
	biggest_len = ft_strlen(map_char[i]);
	while (map_char[i])
	{
		if (ft_strlen(map_char[i]) > biggest_len)
			biggest_len = ft_strlen(map_char[i]);
		i++;
	}
	data->map.map_marc = (char **)malloc(sizeof(char *) * (biggest_len + 1));
	i = 0;
	stock_inversed_map(data, map_char, i);
}
