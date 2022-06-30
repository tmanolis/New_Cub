/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_01_retrieve_floor_ceiling.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msanjuan <msanjuan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 12:02:15 by msanjuan          #+#    #+#             */
/*   Updated: 2022/06/30 12:25:34 by msanjuan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	*copy_into_rgb_array(char **rgb_to_convert, int *rgb)
{
	int		i;

	i = -1;
	while (rgb_to_convert[++i])
	{
		rgb[i] = ft_atoi(rgb_to_convert[i]);
		if (rgb[i] == -1)
			return (0);
	}
	free_double_array(rgb_to_convert);
	return (rgb);
}

/**
 * @brief Get the rgb colors object
 * 			Steps:
 * 			1) Split the line (i.e "      225,30,0") on the commas
 * 			2) Convert the strings (i.e ["  225", "30", "0"]) into ints 
 * 			   using atoi (which manages the whitespaces on its own)
 * 			3) If there are more than 3 numbers, return an error
 *
 * @param line To bypass the letter at the beginning, we sent line + j + 1
 * @return int* - the array of 3 ints (r, g, b)
 */
static int	*get_rgb_colors(char *line)
{
	char	**rgb_to_convert;
	int		*rgb;
	int		count;

	rgb_to_convert = ft_split(line, ',');
	count = 0;
	while (rgb_to_convert[count])
		count++;
	if (count != 3)
	{
		free_double_array(rgb_to_convert);
		return (0);
	}
	rgb = (int *)malloc(sizeof(int) * 3);
	if (!rgb)
		return (0);
	return (copy_into_rgb_array(rgb_to_convert, rgb));
}

// if (line[j + 1] && ft_isprint(line[j + 1]))  
// cas où la ligne c'est : FLOOR 220,100,0 au lieu de F 220,100,0
int	fill_in_the_floor_or_ceiling(t_graphics *graph, char *line, int j)
{
	if (line[j + 1] && ft_isprint(line[j + 1]))
		return (ERR);
	if (!graph->ceiling && line[j] == 'C')
	{
		graph->ceiling = get_rgb_colors(line + j + 1);
		if (graph->ceiling == 0)
			return (ERR);
	}
	else if (!graph->floor && line[j] == 'F')
	{
		graph->floor = get_rgb_colors(line + j + 1);
		if (graph->floor == 0)
			return (ERR);
	}
	else
		return (ERR);
	return (SUCCESS);
}
