/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_check_map_retrieved.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 13:22:39 by msanjuan          #+#    #+#             */
/*   Updated: 2022/06/30 13:27:10 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_letters(t_map *map, char **map_array)
{
	int	i;
	int	j;

	i = 0;
	map->p_direction = '0';
	while (map_array[i] != NULL)
	{
		j = 0;
		while (map_array[i][j])
		{
			while (map->map[i][j] == ' ' || map->map[i][j] == '\t'
			|| map->map[i][j] == '\r'
			|| map->map[i][j] == '\v' || map->map[i][j] == '\f')
				j++;
			if (!(ft_strchr("10NSEW", map_array[i][j])))
				return (print_error("There is an invalid letter in the map"));
			if (ft_strchr("NSEW", map_array[i][j]) && map->p_direction != '0')
				return (print_error("There is more than one player position"));
			if (ft_strchr("NSEW", map_array[i][j]) && map->p_direction == '0')
				map->p_direction = map_array[i][j];
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

static int	check_position_is_valid(t_map *map, char **map_array)
{
	int	i;
	int	j;

	i = map->p_y;
	j = map->p_x;
	if (ft_strlen(map_array[i - 1]) < (size_t)j
		|| ft_strlen(map_array[i + 1]) < (size_t)j
		|| is_a_white_space(map_array[i][j - 1]) == SUCCESS
		|| is_a_white_space(map_array[i][j + 1]) == SUCCESS
		|| is_a_white_space(map_array[i - 1][j]) == SUCCESS
		|| is_a_white_space(map_array[i + 1][j]) == SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

static int	check_player_position(t_map *map, char **map_array)
{
	int	i;
	int	j;

	if (map->p_direction == '0')
		return (print_error("The map should have a player_direction"));
	i = 0;
	while (map_array[i])
	{
		j = 0;
		while (map_array[i][j])
		{
			if (ft_strchr("NSEW", map_array[i][j]))
			{
				map->p_x = j;
				map->p_y = i;
				map_array[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	if (check_position_is_valid(map, map_array) == FAILURE)
		return (print_error("Player position is invalid"));
	return (SUCCESS);
}

static int	check_map_is_at_the_end(t_map *map)
{
	int	i;
	int	j;

	i = map->index_end_of_map;
	while (map->file[i])
	{
		j = 0;
		while (map->file[i][j])
		{
			if (map->file[i][j] != ' ' && map->file[i][j] != '\t'
				&& map->file[i][j] != '\r' && map->file[i][j] != '\n'
				&& map->file[i][j] != '\v' && map->file[i][j] != '\f')
				return (FAILURE);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	check_map_retrieved(t_map *map, char **map_array)
{
	if (map->nb_line < 3)
		return (print_error("The map should be at least 3 lines long."));
	if (check_letters(map, map_array) == FAILURE)
		return (FAILURE);
	if (check_map_sides(map, map_array) == FAILURE)
		return (print_error("The map must be surrounded by walls"));
	if (check_left_side_is_closed(map_array) == FAILURE)
		return (print_error("The map is not fully closed on the left side"));
	if (check_right_side_is_closed(map_array) == FAILURE)
		return (print_error("The map is not fully closed on the right side"));
	if (check_player_position(map, map_array) == FAILURE)
		return (FAILURE);
	if (check_map_is_at_the_end(map) == FAILURE)
		return (print_error("The map description is not the last element"));
	return (SUCCESS);
}
