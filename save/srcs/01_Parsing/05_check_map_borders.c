#include "cub3d.h"

int	check_top_or_bottom(char **map_array, int i, int j)
{
	while (map_array[i][j] == ' ' || map_array[i][j] == '\t' || map_array[i][j] == '\r'
	|| map_array[i][j] == '\v' || map_array[i][j] == '\f')
		j++;
	while (map_array[i][j])
	{
		if (map_array[i][j] != '1')
			return (FAILURE);
		j++;
	}
	return (SUCCESS);
}

int check_map_sides(t_map *map, char **map_array)
{
	int	i;
	int	j;

	if (check_top_or_bottom(map_array, 0, 0) == FAILURE)
		return (FAILURE);
	i = 1;
	while (i < (map->nb_line - 1))
	{
		j = ft_strlen(map_array[i]) - 1;
		if (map_array[i][j] != '1')
			return (FAILURE);
		i++;
	}
	if (check_top_or_bottom(map_array, i, 0) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	check_left_side_is_closed(char **map_array)
{
	int		i;
	int 	j;
	
	j = 0;
	while (map_array[1][j] && (is_a_white_space(map_array[1][j]) == SUCCESS
		|| map_array[1][j] == '1'))
		j++;
	if (map_array[0][j] != '1')
		return (FAILURE);
	i = 2;
	while (map_array[i] && ft_strchr(map_array[i], '0'))
	{
		j = 0;
		while (map_array[i][j] && (is_a_white_space(map_array[i][j]) == SUCCESS
			|| ft_strchr("1NSEW", map_array[i][j])))
			j++;
		if (is_a_white_space(map_array[i - 1][j]) == SUCCESS)
			return (FAILURE);
		if (is_a_white_space(map_array[i + 1][j]) == SUCCESS)
			return (FAILURE);
		if (!ft_strchr("1NSEW", map_array[i][j - 1]))
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

static int	check_first_line_on_right_side(char **map_array)
{
	int 	j;
	
	j = ft_strlen(map_array[1]) - 1;
	while (map_array[1][j] && (is_a_white_space(map_array[1][j]) == SUCCESS
		|| map_array[1][j] == '1'))
		j--;
	if (map_array[0][j] != '1')
		return (FAILURE);
	return (SUCCESS);
}

int	check_right_side_is_closed(char **map_array)
{
	int		i;
	int 	j;
	
	if (check_first_line_on_right_side(map_array) == FAILURE)
		return (FAILURE);
	i = 2; 
	while (map_array[i] && ft_strchr(map_array[i], '0'))
	{
		j = ft_strlen(map_array[i]) - 1;
		while (map_array[i][j] && (is_a_white_space(map_array[i][j]) == SUCCESS
			|| ft_strchr("1NSEW", map_array[i][j])))
			j--;
		if (ft_strlen(map_array[i - 1]) - 1 < (size_t)j
			|| is_a_white_space(map_array[i - 1][j]) == SUCCESS)
			return (FAILURE);
		if (ft_strlen(map_array[i + 1]) - 1 < (size_t)j
			|| is_a_white_space(map_array[i + 1][j]) == SUCCESS)
			return (FAILURE);
		if (!ft_strchr("1NSEW", map_array[i][j + 1]))
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}